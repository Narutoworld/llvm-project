//===-- BreakpointSite.cpp --------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "lldb/Breakpoint/BreakpointSite.h"

// C Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "lldb/Breakpoint/BreakpointLocation.h"
#include "lldb/Breakpoint/BreakpointSiteList.h"

using namespace lldb;
using namespace lldb_private;

BreakpointSite::BreakpointSite
(
    BreakpointSiteList *list,
    BreakpointLocationSP& owner,
    lldb::addr_t addr,
    lldb::tid_t tid,
    bool use_hardware
) :
    StoppointLocation(GetNextID(), addr, tid, use_hardware),
    m_type (eSoftware), // Process subclasses need to set this correctly using SetType()
    m_saved_opcode(),
    m_trap_opcode(),
    m_enabled(false), // Need to create it disabled, so the first enable turns it on.
    m_owners()
{
    m_owners.Add(owner);
}

BreakpointSite::~BreakpointSite()
{
    BreakpointLocationSP bp_loc_sp;
    for (int i = 0; i < m_owners.GetSize(); i++)
    {
        m_owners.GetByIndex(i)->ClearBreakpointSite();
    }
}

break_id_t
BreakpointSite::GetNextID()
{
    static break_id_t g_next_id = 0;
    return ++g_next_id;
}

// RETURNS - true if we should stop at this breakpoint, false if we
// should continue.

bool
BreakpointSite::ShouldStop (StoppointCallbackContext *context)
{
    m_hit_count++;
    return m_owners.ShouldStop (context);
}

bool
BreakpointSite::IsBreakpointAtThisSite (lldb::break_id_t bp_id)
{
    for (int i = 0; i < m_owners.GetSize(); i++)
    {
        if (m_owners.GetByIndex(i)->GetBreakpoint().GetID() == bp_id)
            return true;
    }
    return false;
}

void
BreakpointSite::Dump(Stream *s) const
{
    if (s == NULL)
        return;

    s->Printf("BreakpointSite %u: tid = %4.4x  addr = 0x%8.8llx  type = %s breakpoint  hw_index = %i  hit_count = %-4u",
            GetID(),
            m_tid,
            (uint64_t)m_addr,
            IsHardware() ? "hardware" : "software",
            GetHardwareIndex(),
            GetHitCount());
}

void
BreakpointSite::GetDescription (Stream *s, lldb::DescriptionLevel level)
{
    if (level != lldb::eDescriptionLevelBrief)
        s->Printf ("breakpoint site: %d ", GetID());
    m_owners.GetDescription (s, level);
}

uint8_t *
BreakpointSite::GetTrapOpcodeBytes()
{
    return &m_trap_opcode[0];
}

const uint8_t *
BreakpointSite::GetTrapOpcodeBytes() const
{
    return &m_trap_opcode[0];
}

size_t
BreakpointSite::GetTrapOpcodeMaxByteSize() const
{
    return sizeof(m_trap_opcode);
}

bool
BreakpointSite::SetTrapOpcode (const uint8_t *trap_opcode, size_t trap_opcode_size)
{
    if (trap_opcode_size > 0 && trap_opcode_size <= sizeof(m_trap_opcode))
    {
        m_byte_size = trap_opcode_size;
        ::memcpy (m_trap_opcode, trap_opcode, trap_opcode_size);
        return true;
    }
    m_byte_size = 0;
    return false;
}

uint8_t *
BreakpointSite::GetSavedOpcodeBytes()
{
    return &m_saved_opcode[0];
}

const uint8_t *
BreakpointSite::GetSavedOpcodeBytes() const
{
    return &m_saved_opcode[0];
}

bool
BreakpointSite::IsEnabled () const
{
    return m_enabled;
}

void
BreakpointSite::SetEnabled (bool enabled)
{
    m_enabled = enabled;
}

void
BreakpointSite::AddOwner (BreakpointLocationSP &owner)
{
    m_owners.Add(owner);
}

uint32_t
BreakpointSite::RemoveOwner (lldb::user_id_t break_id, lldb::user_id_t break_loc_id)
{
    m_owners.Remove(break_id, break_loc_id);
    return m_owners.GetSize();
}

uint32_t
BreakpointSite::GetNumberOfOwners ()
{
    return m_owners.GetSize();
}

BreakpointLocationSP
BreakpointSite::GetOwnerAtIndex (uint32_t index)
{
    return m_owners.GetByIndex (index);
}

bool
BreakpointSite::IntersectsRange(lldb::addr_t addr, size_t size, lldb::addr_t *intersect_addr, size_t *intersect_size, size_t *opcode_offset) const
{
    // We only use software traps for software breakpoints
    if (!IsHardware())
    {
        if (m_byte_size > 0)
        {
            const lldb::addr_t bp_end_addr = m_addr + m_byte_size;
            const lldb::addr_t end_addr = addr + size;
            // Is the breakpoint end address before the passed in start address?
            if (bp_end_addr <= addr)
                return false;
            // Is the breakpoint start address after passed in end address?
            if (end_addr <= m_addr)
                return false;
            if (intersect_addr || intersect_size || opcode_offset)
            {
                if (m_addr < addr)
                {
                    if (intersect_addr)
                        *intersect_addr = addr;
                    if (intersect_size)
                        *intersect_size = std::min<lldb::addr_t>(bp_end_addr, end_addr) - addr;
                    if (opcode_offset)
                        *opcode_offset = addr - m_addr;
                }
                else
                {
                    if (intersect_addr)
                        *intersect_addr = m_addr;
                    if (intersect_size)
                        *intersect_size = std::min<lldb::addr_t>(bp_end_addr, end_addr) - m_addr;
                    if (opcode_offset)
                        *opcode_offset = 0;
                }
            }
            return true;
        }
    }
    return false;
}
