// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// REQUIRES: aarch64-registered-target
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -msve-vector-bits=512 -fallow-half-arguments-and-returns -fno-experimental-new-pass-manager -S -O1 -emit-llvm -o - %s | FileCheck %s

#include <arm_sve.h>

#define N __ARM_FEATURE_SVE_BITS

typedef svint32_t fixed_int32_t __attribute__((arm_sve_vector_bits(N)));
typedef svfloat64_t fixed_float64_t __attribute__((arm_sve_vector_bits(N)));
typedef svbool_t fixed_bool_t __attribute__((arm_sve_vector_bits(N)));

//===----------------------------------------------------------------------===//
// Test caller/callee with VLST <-> VLAT
//===----------------------------------------------------------------------===//

// CHECK-LABEL: @sizeless_callee(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <vscale x 4 x i32> [[X:%.*]]
//
svint32_t sizeless_callee(svint32_t x) {
  return x;
}

// CHECK-LABEL: @fixed_caller(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[X:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[X_ADDR:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <16 x i32>* [[X]] to <vscale x 4 x i32>*
// CHECK-NEXT:    store <vscale x 4 x i32> [[X_COERCE:%.*]], <vscale x 4 x i32>* [[TMP0]], align 16
// CHECK-NEXT:    [[X1:%.*]] = load <16 x i32>, <16 x i32>* [[X]], align 16, [[TBAA6:!tbaa !.*]]
// CHECK-NEXT:    store <16 x i32> [[X1]], <16 x i32>* [[X_ADDR]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <16 x i32>* [[X_ADDR]] to <vscale x 4 x i32>*
// CHECK-NEXT:    [[TMP2:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[TMP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    store <vscale x 4 x i32> [[TMP2]], <vscale x 4 x i32>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA9:!tbaa !.*]]
// CHECK-NEXT:    [[CASTFIXEDSVE:%.*]] = bitcast <vscale x 4 x i32>* [[SAVED_CALL_RVALUE]] to <16 x i32>*
// CHECK-NEXT:    [[TMP3:%.*]] = load <16 x i32>, <16 x i32>* [[CASTFIXEDSVE]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[RETVAL_0__SROA_CAST:%.*]] = bitcast <vscale x 4 x i32>* [[RETVAL_COERCE]] to <16 x i32>*
// CHECK-NEXT:    store <16 x i32> [[TMP3]], <16 x i32>* [[RETVAL_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP4:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 4 x i32> [[TMP4]]
//
fixed_int32_t fixed_caller(fixed_int32_t x) {
  return sizeless_callee(x);
}

// CHECK-LABEL: @fixed_callee(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[X:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <16 x i32>* [[X]] to <vscale x 4 x i32>*
// CHECK-NEXT:    store <vscale x 4 x i32> [[X_COERCE:%.*]], <vscale x 4 x i32>* [[TMP0]], align 16
// CHECK-NEXT:    [[X1:%.*]] = load <16 x i32>, <16 x i32>* [[X]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[RETVAL_0__SROA_CAST:%.*]] = bitcast <vscale x 4 x i32>* [[RETVAL_COERCE]] to <16 x i32>*
// CHECK-NEXT:    store <16 x i32> [[X1]], <16 x i32>* [[RETVAL_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP1:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 4 x i32> [[TMP1]]
//
fixed_int32_t fixed_callee(fixed_int32_t x) {
  return x;
}

// CHECK-LABEL: @sizeless_caller(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[X_ADDR:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[COERCE_COERCE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[COERCE1:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <16 x i32>, align 64
// CHECK-NEXT:    store <vscale x 4 x i32> [[X:%.*]], <vscale x 4 x i32>* [[X_ADDR]], align 16, [[TBAA9]]
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <vscale x 4 x i32>* [[X_ADDR]] to <16 x i32>*
// CHECK-NEXT:    [[TMP1:%.*]] = load <16 x i32>, <16 x i32>* [[TMP0]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[COERCE_0__SROA_CAST:%.*]] = bitcast <vscale x 4 x i32>* [[COERCE_COERCE]] to <16 x i32>*
// CHECK-NEXT:    store <16 x i32> [[TMP1]], <16 x i32>* [[COERCE_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP2:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[COERCE_COERCE]], align 16
// CHECK-NEXT:    [[CALL:%.*]] = call <vscale x 4 x i32> @fixed_callee(<vscale x 4 x i32> [[TMP2]])
// CHECK-NEXT:    [[TMP3:%.*]] = bitcast <16 x i32>* [[COERCE1]] to <vscale x 4 x i32>*
// CHECK-NEXT:    store <vscale x 4 x i32> [[CALL]], <vscale x 4 x i32>* [[TMP3]], align 16
// CHECK-NEXT:    [[TMP4:%.*]] = load <16 x i32>, <16 x i32>* [[COERCE1]], align 16, [[TBAA6]]
// CHECK-NEXT:    store <16 x i32> [[TMP4]], <16 x i32>* [[SAVED_CALL_RVALUE]], align 64, [[TBAA6]]
// CHECK-NEXT:    [[CASTFIXEDSVE:%.*]] = bitcast <16 x i32>* [[SAVED_CALL_RVALUE]] to <vscale x 4 x i32>*
// CHECK-NEXT:    [[TMP5:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[CASTFIXEDSVE]], align 64, [[TBAA6]]
// CHECK-NEXT:    ret <vscale x 4 x i32> [[TMP5]]
//
svint32_t sizeless_caller(svint32_t x) {
  return fixed_callee(x);
}

//===----------------------------------------------------------------------===//
// fixed, fixed
//===----------------------------------------------------------------------===//

// CHECK-LABEL: @call_int32_ff(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[OP1:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[OP2:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[OP1_ADDR:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[OP2_ADDR:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <16 x i32>* [[OP1]] to <vscale x 4 x i32>*
// CHECK-NEXT:    store <vscale x 4 x i32> [[OP1_COERCE:%.*]], <vscale x 4 x i32>* [[TMP0]], align 16
// CHECK-NEXT:    [[OP11:%.*]] = load <16 x i32>, <16 x i32>* [[OP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <16 x i32>* [[OP2]] to <vscale x 4 x i32>*
// CHECK-NEXT:    store <vscale x 4 x i32> [[OP2_COERCE:%.*]], <vscale x 4 x i32>* [[TMP1]], align 16
// CHECK-NEXT:    [[OP22:%.*]] = load <16 x i32>, <16 x i32>* [[OP2]], align 16, [[TBAA6]]
// CHECK-NEXT:    store <16 x i32> [[OP11]], <16 x i32>* [[OP1_ADDR]], align 16, [[TBAA6]]
// CHECK-NEXT:    store <16 x i32> [[OP22]], <16 x i32>* [[OP2_ADDR]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <16 x i32>* [[OP1_ADDR]] to <vscale x 4 x i32>*
// CHECK-NEXT:    [[TMP3:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[TMP2]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP4:%.*]] = bitcast <16 x i32>* [[OP2_ADDR]] to <vscale x 4 x i32>*
// CHECK-NEXT:    [[TMP5:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[TMP4]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP6:%.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> [[PG:%.*]])
// CHECK-NEXT:    [[TMP7:%.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.sel.nxv4i32(<vscale x 4 x i1> [[TMP6]], <vscale x 4 x i32> [[TMP3]], <vscale x 4 x i32> [[TMP5]])
// CHECK-NEXT:    store <vscale x 4 x i32> [[TMP7]], <vscale x 4 x i32>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA9]]
// CHECK-NEXT:    [[CASTFIXEDSVE:%.*]] = bitcast <vscale x 4 x i32>* [[SAVED_CALL_RVALUE]] to <16 x i32>*
// CHECK-NEXT:    [[TMP8:%.*]] = load <16 x i32>, <16 x i32>* [[CASTFIXEDSVE]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[RETVAL_0__SROA_CAST:%.*]] = bitcast <vscale x 4 x i32>* [[RETVAL_COERCE]] to <16 x i32>*
// CHECK-NEXT:    store <16 x i32> [[TMP8]], <16 x i32>* [[RETVAL_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP9:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 4 x i32> [[TMP9]]
//
fixed_int32_t call_int32_ff(svbool_t pg, fixed_int32_t op1, fixed_int32_t op2) {
  return svsel(pg, op1, op2);
}

// CHECK-LABEL: @call_float64_ff(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[OP1:%.*]] = alloca <8 x double>, align 16
// CHECK-NEXT:    [[OP2:%.*]] = alloca <8 x double>, align 16
// CHECK-NEXT:    [[OP1_ADDR:%.*]] = alloca <8 x double>, align 16
// CHECK-NEXT:    [[OP2_ADDR:%.*]] = alloca <8 x double>, align 16
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 2 x double>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 2 x double>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <8 x double>* [[OP1]] to <vscale x 2 x double>*
// CHECK-NEXT:    store <vscale x 2 x double> [[OP1_COERCE:%.*]], <vscale x 2 x double>* [[TMP0]], align 16
// CHECK-NEXT:    [[OP11:%.*]] = load <8 x double>, <8 x double>* [[OP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <8 x double>* [[OP2]] to <vscale x 2 x double>*
// CHECK-NEXT:    store <vscale x 2 x double> [[OP2_COERCE:%.*]], <vscale x 2 x double>* [[TMP1]], align 16
// CHECK-NEXT:    [[OP22:%.*]] = load <8 x double>, <8 x double>* [[OP2]], align 16, [[TBAA6]]
// CHECK-NEXT:    store <8 x double> [[OP11]], <8 x double>* [[OP1_ADDR]], align 16, [[TBAA6]]
// CHECK-NEXT:    store <8 x double> [[OP22]], <8 x double>* [[OP2_ADDR]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <8 x double>* [[OP1_ADDR]] to <vscale x 2 x double>*
// CHECK-NEXT:    [[TMP3:%.*]] = load <vscale x 2 x double>, <vscale x 2 x double>* [[TMP2]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP4:%.*]] = bitcast <8 x double>* [[OP2_ADDR]] to <vscale x 2 x double>*
// CHECK-NEXT:    [[TMP5:%.*]] = load <vscale x 2 x double>, <vscale x 2 x double>* [[TMP4]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP6:%.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> [[PG:%.*]])
// CHECK-NEXT:    [[TMP7:%.*]] = call <vscale x 2 x double> @llvm.aarch64.sve.sel.nxv2f64(<vscale x 2 x i1> [[TMP6]], <vscale x 2 x double> [[TMP3]], <vscale x 2 x double> [[TMP5]])
// CHECK-NEXT:    store <vscale x 2 x double> [[TMP7]], <vscale x 2 x double>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA11:!tbaa !.*]]
// CHECK-NEXT:    [[CASTFIXEDSVE:%.*]] = bitcast <vscale x 2 x double>* [[SAVED_CALL_RVALUE]] to <8 x double>*
// CHECK-NEXT:    [[TMP8:%.*]] = load <8 x double>, <8 x double>* [[CASTFIXEDSVE]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[RETVAL_0__SROA_CAST:%.*]] = bitcast <vscale x 2 x double>* [[RETVAL_COERCE]] to <8 x double>*
// CHECK-NEXT:    store <8 x double> [[TMP8]], <8 x double>* [[RETVAL_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP9:%.*]] = load <vscale x 2 x double>, <vscale x 2 x double>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 2 x double> [[TMP9]]
//
fixed_float64_t call_float64_ff(svbool_t pg, fixed_float64_t op1, fixed_float64_t op2) {
  return svsel(pg, op1, op2);
}

// CHECK-LABEL: @call_bool_ff(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[OP1:%.*]] = alloca <8 x i8>, align 16
// CHECK-NEXT:    [[OP2:%.*]] = alloca <8 x i8>, align 16
// CHECK-NEXT:    [[OP1_ADDR:%.*]] = alloca <8 x i8>, align 16
// CHECK-NEXT:    [[OP2_ADDR:%.*]] = alloca <8 x i8>, align 16
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <8 x i8>* [[OP1]] to <vscale x 16 x i1>*
// CHECK-NEXT:    store <vscale x 16 x i1> [[OP1_COERCE:%.*]], <vscale x 16 x i1>* [[TMP0]], align 16
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <8 x i8>* [[OP1]] to i64*
// CHECK-NEXT:    [[OP113:%.*]] = load i64, i64* [[TMP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <8 x i8>* [[OP2]] to <vscale x 16 x i1>*
// CHECK-NEXT:    store <vscale x 16 x i1> [[OP2_COERCE:%.*]], <vscale x 16 x i1>* [[TMP2]], align 16
// CHECK-NEXT:    [[TMP3:%.*]] = bitcast <8 x i8>* [[OP2]] to i64*
// CHECK-NEXT:    [[OP224:%.*]] = load i64, i64* [[TMP3]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP4:%.*]] = bitcast <8 x i8>* [[OP1_ADDR]] to i64*
// CHECK-NEXT:    store i64 [[OP113]], i64* [[TMP4]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP5:%.*]] = bitcast <8 x i8>* [[OP2_ADDR]] to i64*
// CHECK-NEXT:    store i64 [[OP224]], i64* [[TMP5]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP6:%.*]] = bitcast <8 x i8>* [[OP1_ADDR]] to <vscale x 16 x i1>*
// CHECK-NEXT:    [[TMP7:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[TMP6]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP8:%.*]] = bitcast <8 x i8>* [[OP2_ADDR]] to <vscale x 16 x i1>*
// CHECK-NEXT:    [[TMP9:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[TMP8]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP10:%.*]] = call <vscale x 16 x i1> @llvm.aarch64.sve.sel.nxv16i1(<vscale x 16 x i1> [[PG:%.*]], <vscale x 16 x i1> [[TMP7]], <vscale x 16 x i1> [[TMP9]])
// CHECK-NEXT:    store <vscale x 16 x i1> [[TMP10]], <vscale x 16 x i1>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA13:!tbaa !.*]]
// CHECK-NEXT:    [[TMP11:%.*]] = bitcast <vscale x 16 x i1>* [[SAVED_CALL_RVALUE]] to i64*
// CHECK-NEXT:    [[TMP12:%.*]] = load i64, i64* [[TMP11]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP13:%.*]] = bitcast <vscale x 16 x i1>* [[RETVAL_COERCE]] to i64*
// CHECK-NEXT:    store i64 [[TMP12]], i64* [[TMP13]], align 16
// CHECK-NEXT:    [[TMP14:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 16 x i1> [[TMP14]]
//
fixed_bool_t call_bool_ff(svbool_t pg, fixed_bool_t op1, fixed_bool_t op2) {
  return svsel(pg, op1, op2);
}

//===----------------------------------------------------------------------===//
// fixed, scalable
//===----------------------------------------------------------------------===//

// CHECK-LABEL: @call_int32_fs(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[OP1:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[OP1_ADDR:%.*]] = alloca <16 x i32>, align 16
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <16 x i32>* [[OP1]] to <vscale x 4 x i32>*
// CHECK-NEXT:    store <vscale x 4 x i32> [[OP1_COERCE:%.*]], <vscale x 4 x i32>* [[TMP0]], align 16
// CHECK-NEXT:    [[OP11:%.*]] = load <16 x i32>, <16 x i32>* [[OP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    store <16 x i32> [[OP11]], <16 x i32>* [[OP1_ADDR]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <16 x i32>* [[OP1_ADDR]] to <vscale x 4 x i32>*
// CHECK-NEXT:    [[TMP2:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[TMP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP3:%.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> [[PG:%.*]])
// CHECK-NEXT:    [[TMP4:%.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.sel.nxv4i32(<vscale x 4 x i1> [[TMP3]], <vscale x 4 x i32> [[TMP2]], <vscale x 4 x i32> [[OP2:%.*]])
// CHECK-NEXT:    store <vscale x 4 x i32> [[TMP4]], <vscale x 4 x i32>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA9]]
// CHECK-NEXT:    [[CASTFIXEDSVE:%.*]] = bitcast <vscale x 4 x i32>* [[SAVED_CALL_RVALUE]] to <16 x i32>*
// CHECK-NEXT:    [[TMP5:%.*]] = load <16 x i32>, <16 x i32>* [[CASTFIXEDSVE]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[RETVAL_0__SROA_CAST:%.*]] = bitcast <vscale x 4 x i32>* [[RETVAL_COERCE]] to <16 x i32>*
// CHECK-NEXT:    store <16 x i32> [[TMP5]], <16 x i32>* [[RETVAL_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP6:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 4 x i32> [[TMP6]]
//
fixed_int32_t call_int32_fs(svbool_t pg, fixed_int32_t op1, svint32_t op2) {
  return svsel(pg, op1, op2);
}

// CHECK-LABEL: @call_float64_fs(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[OP1:%.*]] = alloca <8 x double>, align 16
// CHECK-NEXT:    [[OP1_ADDR:%.*]] = alloca <8 x double>, align 16
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 2 x double>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 2 x double>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <8 x double>* [[OP1]] to <vscale x 2 x double>*
// CHECK-NEXT:    store <vscale x 2 x double> [[OP1_COERCE:%.*]], <vscale x 2 x double>* [[TMP0]], align 16
// CHECK-NEXT:    [[OP11:%.*]] = load <8 x double>, <8 x double>* [[OP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    store <8 x double> [[OP11]], <8 x double>* [[OP1_ADDR]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <8 x double>* [[OP1_ADDR]] to <vscale x 2 x double>*
// CHECK-NEXT:    [[TMP2:%.*]] = load <vscale x 2 x double>, <vscale x 2 x double>* [[TMP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP3:%.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> [[PG:%.*]])
// CHECK-NEXT:    [[TMP4:%.*]] = call <vscale x 2 x double> @llvm.aarch64.sve.sel.nxv2f64(<vscale x 2 x i1> [[TMP3]], <vscale x 2 x double> [[TMP2]], <vscale x 2 x double> [[OP2:%.*]])
// CHECK-NEXT:    store <vscale x 2 x double> [[TMP4]], <vscale x 2 x double>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA11]]
// CHECK-NEXT:    [[CASTFIXEDSVE:%.*]] = bitcast <vscale x 2 x double>* [[SAVED_CALL_RVALUE]] to <8 x double>*
// CHECK-NEXT:    [[TMP5:%.*]] = load <8 x double>, <8 x double>* [[CASTFIXEDSVE]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[RETVAL_0__SROA_CAST:%.*]] = bitcast <vscale x 2 x double>* [[RETVAL_COERCE]] to <8 x double>*
// CHECK-NEXT:    store <8 x double> [[TMP5]], <8 x double>* [[RETVAL_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP6:%.*]] = load <vscale x 2 x double>, <vscale x 2 x double>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 2 x double> [[TMP6]]
//
fixed_float64_t call_float64_fs(svbool_t pg, fixed_float64_t op1, svfloat64_t op2) {
  return svsel(pg, op1, op2);
}

// CHECK-LABEL: @call_bool_fs(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[OP1:%.*]] = alloca <8 x i8>, align 16
// CHECK-NEXT:    [[OP1_ADDR:%.*]] = alloca <8 x i8>, align 16
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <8 x i8>* [[OP1]] to <vscale x 16 x i1>*
// CHECK-NEXT:    store <vscale x 16 x i1> [[OP1_COERCE:%.*]], <vscale x 16 x i1>* [[TMP0]], align 16
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <8 x i8>* [[OP1]] to i64*
// CHECK-NEXT:    [[OP112:%.*]] = load i64, i64* [[TMP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <8 x i8>* [[OP1_ADDR]] to i64*
// CHECK-NEXT:    store i64 [[OP112]], i64* [[TMP2]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP3:%.*]] = bitcast <8 x i8>* [[OP1_ADDR]] to <vscale x 16 x i1>*
// CHECK-NEXT:    [[TMP4:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[TMP3]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP5:%.*]] = call <vscale x 16 x i1> @llvm.aarch64.sve.sel.nxv16i1(<vscale x 16 x i1> [[PG:%.*]], <vscale x 16 x i1> [[TMP4]], <vscale x 16 x i1> [[OP2:%.*]])
// CHECK-NEXT:    store <vscale x 16 x i1> [[TMP5]], <vscale x 16 x i1>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA13]]
// CHECK-NEXT:    [[TMP6:%.*]] = bitcast <vscale x 16 x i1>* [[SAVED_CALL_RVALUE]] to i64*
// CHECK-NEXT:    [[TMP7:%.*]] = load i64, i64* [[TMP6]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP8:%.*]] = bitcast <vscale x 16 x i1>* [[RETVAL_COERCE]] to i64*
// CHECK-NEXT:    store i64 [[TMP7]], i64* [[TMP8]], align 16
// CHECK-NEXT:    [[TMP9:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 16 x i1> [[TMP9]]
//
fixed_bool_t call_bool_fs(svbool_t pg, fixed_bool_t op1, svbool_t op2) {
  return svsel(pg, op1, op2);
}

//===----------------------------------------------------------------------===//
// scalable, scalable
//===----------------------------------------------------------------------===//

// CHECK-LABEL: @call_int32_ss(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 4 x i32>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> [[PG:%.*]])
// CHECK-NEXT:    [[TMP1:%.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.sel.nxv4i32(<vscale x 4 x i1> [[TMP0]], <vscale x 4 x i32> [[OP1:%.*]], <vscale x 4 x i32> [[OP2:%.*]])
// CHECK-NEXT:    store <vscale x 4 x i32> [[TMP1]], <vscale x 4 x i32>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA9]]
// CHECK-NEXT:    [[CASTFIXEDSVE:%.*]] = bitcast <vscale x 4 x i32>* [[SAVED_CALL_RVALUE]] to <16 x i32>*
// CHECK-NEXT:    [[TMP2:%.*]] = load <16 x i32>, <16 x i32>* [[CASTFIXEDSVE]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[RETVAL_0__SROA_CAST:%.*]] = bitcast <vscale x 4 x i32>* [[RETVAL_COERCE]] to <16 x i32>*
// CHECK-NEXT:    store <16 x i32> [[TMP2]], <16 x i32>* [[RETVAL_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP3:%.*]] = load <vscale x 4 x i32>, <vscale x 4 x i32>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 4 x i32> [[TMP3]]
//
fixed_int32_t call_int32_ss(svbool_t pg, svint32_t op1, svint32_t op2) {
  return svsel(pg, op1, op2);
}

// CHECK-LABEL: @call_float64_ss(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 2 x double>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 2 x double>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> [[PG:%.*]])
// CHECK-NEXT:    [[TMP1:%.*]] = call <vscale x 2 x double> @llvm.aarch64.sve.sel.nxv2f64(<vscale x 2 x i1> [[TMP0]], <vscale x 2 x double> [[OP1:%.*]], <vscale x 2 x double> [[OP2:%.*]])
// CHECK-NEXT:    store <vscale x 2 x double> [[TMP1]], <vscale x 2 x double>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA11]]
// CHECK-NEXT:    [[CASTFIXEDSVE:%.*]] = bitcast <vscale x 2 x double>* [[SAVED_CALL_RVALUE]] to <8 x double>*
// CHECK-NEXT:    [[TMP2:%.*]] = load <8 x double>, <8 x double>* [[CASTFIXEDSVE]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[RETVAL_0__SROA_CAST:%.*]] = bitcast <vscale x 2 x double>* [[RETVAL_COERCE]] to <8 x double>*
// CHECK-NEXT:    store <8 x double> [[TMP2]], <8 x double>* [[RETVAL_0__SROA_CAST]], align 16
// CHECK-NEXT:    [[TMP3:%.*]] = load <vscale x 2 x double>, <vscale x 2 x double>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 2 x double> [[TMP3]]
//
fixed_float64_t call_float64_ss(svbool_t pg, svfloat64_t op1, svfloat64_t op2) {
  return svsel(pg, op1, op2);
}

// CHECK-LABEL: @call_bool_ss(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[SAVED_CALL_RVALUE:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-NEXT:    [[RETVAL_COERCE:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i1> @llvm.aarch64.sve.sel.nxv16i1(<vscale x 16 x i1> [[PG:%.*]], <vscale x 16 x i1> [[OP1:%.*]], <vscale x 16 x i1> [[OP2:%.*]])
// CHECK-NEXT:    store <vscale x 16 x i1> [[TMP0]], <vscale x 16 x i1>* [[SAVED_CALL_RVALUE]], align 16, [[TBAA13]]
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <vscale x 16 x i1>* [[SAVED_CALL_RVALUE]] to i64*
// CHECK-NEXT:    [[TMP2:%.*]] = load i64, i64* [[TMP1]], align 16, [[TBAA6]]
// CHECK-NEXT:    [[TMP3:%.*]] = bitcast <vscale x 16 x i1>* [[RETVAL_COERCE]] to i64*
// CHECK-NEXT:    store i64 [[TMP2]], i64* [[TMP3]], align 16
// CHECK-NEXT:    [[TMP4:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[RETVAL_COERCE]], align 16
// CHECK-NEXT:    ret <vscale x 16 x i1> [[TMP4]]
//
fixed_bool_t call_bool_ss(svbool_t pg, svbool_t op1, svbool_t op2) {
  return svsel(pg, op1, op2);
}
