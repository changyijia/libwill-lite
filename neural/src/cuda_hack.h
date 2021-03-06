#pragma once

#include "cudnn.h"

//默认使用的是cudnn5，这里是在其他版本，或者没有cuda的情况下，对原来的函数进行一些类似hack的处理

#ifdef _NO_CUDA
//在cuda不生效的时候，屏蔽所有使用过的cuda函数
//这个方法不知道好不好
#define Cublas Cblas

#define cudaMalloc (0)
#define cudaFree (0)
#define cudaMemcpy (0)

#define cuda_addnumber (0)
#define cuda_reciprocal (0)

#define curandGenerator_t int*
#define curandCreateGenerator (0)
#define curandDestroyGenerator (0)
#define curandSetPseudoRandomGeneratorSeed (0)
#define curandGenerateUniform (0)
#define curandGenerateUniformDouble (0)

#define cudnnHandle_t int*
#define cudnnStatus_t int

#define cudnnTensorDescriptor_t int*
#define cudnnPoolingDescriptor_t int*
#define cudnnConvolutionDescriptor_t int*
#define cudnnFilterDescriptor_t int*

#define cudnnSetTensor4dDescriptor (0)
#define cudnnSetPooling2dDescriptor (0)
#define cudnnSetTensor (0)

#define cudnnGetTensor4dDescriptor (0)
#define cudnnSetConvolution2dDescriptor (0)
#define cudnnSetFilter4dDescriptor (0)
#define cudnnConvolutionForward (0)
#define cudnnConvolutionBackwardData (0)
#define cudnnConvolutionBackwardFilter (0)
#define cudnnConvolutionBackwardBias (0)

#define cudnnPoolingForward (0)
#define cudnnPoolingBackward (0)

#define cudnnSoftmaxForward (0)
#define cudnnSoftmaxBackward (0)

#define cudnnActivationDescriptor_t int*
#define cudnnOpTensorDescriptor_t int*

#define cudnnCreatetOpTensorDescriptor (0)
#define cudnnDestroytOpTensorDescriptor (0)
#define cudnnSetOpTensorDescriptor (0)
#define cudnnOpTensor (0)

#define cudnnCreateActivationDescriptor (0)
#define cudnnDestroyActivationDescriptor (0)
#define cudnnSetActivationDescriptor (0)
#define cudnnActivationForward (0)
#define cudnnActivationBackward (0)

#define cudnnCreate (0)
#define cudnnDestroy (0)
#define cudnnAddTensor (0)

#endif

//判断cudnn版本2.0实际上只用于TK1，未完成
#if CUDNN_VERSION == 2000 || (defined _NO_CUDA)
#define cudnnRNNDescriptor_t int*
#define cudnnDropoutDescriptor_t int*
#define cudnnSpatialTransformerDescriptor_t int*
#define cudnnLRNDescriptor_t int*



#define cudnnFindConvolutionForwardAlgorithm (0)
#define cudnnFindConvolutionBackwardDataAlgorithm (0)
#define cudnnFindConvolutionBackwardFilterAlgorithm (0)

#define cudnnSetDropoutDescriptor (0)
#define cudnnDropoutForward (0)
#define cudnnDropoutBackward (0)
#define cudnnDropoutGetStatesSize (0)
#define cudnnDropoutGetReserveSpaceSize (0)

#define cudnnDivisiveNormalizationForward (0)
#define cudnnDivisiveNormalizationBackward (0)

#define cudnnBatchNormalizationForwardInference (0)
#define cudnnBatchNormalizationForwardTraining (0)
#define cudnnBatchNormalizationBackward (0)
#define cudnnDeriveBNTensorDescriptor (0)

#define cudnnSetLRNDescriptor (0)
#define cudnnLRNCrossChannelForward (0)
#define cudnnLRNCrossChannelBackward (0)

#define cudnnSetSpatialTransformerNdDescriptor (0)
#define cudnnSpatialTfGridGeneratorForward (0)
#define cudnnSpatialTfSamplerForward (0)
#define cudnnSpatialTfSamplerBackward (0)
#define cudnnSpatialTfGridGeneratorBackward (0)

#define cudnnRNNForwardInference (0)
#define cudnnRNNBackwardData (0)
#define cudnnRNNBackwardWeights (0)

#endif

#if CUDNN_VERSION == 2000

#define CUDNN_NOT_PROPAGATE_NAN 0
#define CUDNN_ACTIVATION_CLIPPED_RELU cudnnActivationMode_t(CUDNN_ACTIVATION_TANH + 1)
#define CUDNN_LRN_CROSS_CHANNEL_DIM1 0
#define CUDNN_SAMPLER_BILINEAR 0
#define CUDNN_DIVNORM_PRECOMPUTED_MEANS 0
#define CUDNN_SOFTMAX_LOG CUDNN_SOFTMAX_FAST

//复制自cudnn5，只是为了使代码可以通过
typedef enum
{
    CUDNN_BATCHNORM_PER_ACTIVATION = 0,
    CUDNN_BATCHNORM_SPATIAL = 1,
} cudnnBatchNormMode_t;

typedef enum
{
    CUDNN_RNN_RELU = 0,
    CUDNN_RNN_TANH = 1,
    CUDNN_LSTM = 2,
    CUDNN_GRU = 3
} cudnnRNNMode_t;

typedef enum
{
    CUDNN_UNIDIRECTIONAL = 0,
    CUDNN_BIDIRECTIONAL = 1
} cudnnDirectionMode_t;

typedef enum
{
    CUDNN_LINEAR_INPUT = 0,
    CUDNN_SKIP_INPUT = 1
} cudnnRNNInputMode_t;


typedef enum
{
    CUDNN_OP_TENSOR_ADD = 0,
    CUDNN_OP_TENSOR_MUL = 1,
    CUDNN_OP_TENSOR_MIN = 2,
    CUDNN_OP_TENSOR_MAX = 3,
} cudnnOpTensorOp_t;

typedef struct
{
    cudnnConvolutionFwdAlgo_t algo = CUDNN_CONVOLUTION_FWD_ALGO_IMPLICIT_GEMM;
    cudnnStatus_t status;
    float time;
    size_t memory;
} cudnnConvolutionFwdAlgoPerf_t;

typedef int cudnnConvolutionBwdFilterAlgo_t;
typedef struct
{
    cudnnConvolutionBwdFilterAlgo_t algo;
    cudnnStatus_t status;
    float time;
    size_t memory;
} cudnnConvolutionBwdFilterAlgoPerf_t;

typedef int cudnnConvolutionBwdDataAlgo_t;
typedef struct
{
    cudnnConvolutionBwdDataAlgo_t algo;
    cudnnStatus_t status;
    float time;
    size_t memory;
} cudnnConvolutionBwdDataAlgoPerf_t;

typedef cudnnOpTensorOp_t* cudnnOpTensorDescriptor_t;
typedef cudnnActivationMode_t* cudnnActivationDescriptor_t;

cudnnStatus_t cudnnCreateOpTensorDescriptor(cudnnOpTensorDescriptor_t*);
cudnnStatus_t cudnnDestroyOpTensorDescriptor(cudnnOpTensorDescriptor_t);
cudnnStatus_t cudnnSetOpTensorDescriptor(cudnnOpTensorDescriptor_t, cudnnOpTensorOp_t, cudnnDataType_t, int);
/* Tensor Bias operation : C = op( alpha1 * A, alpha2 * B ) + beta * C */
cudnnStatus_t cudnnOpTensor(cudnnHandle_t, const cudnnOpTensorDescriptor_t, const void*, const cudnnTensorDescriptor_t, const void*, const void*,
    const cudnnTensorDescriptor_t, const void*, const void*, const cudnnTensorDescriptor_t, void*);

cudnnStatus_t cudnnCreateActivationDescriptor(cudnnActivationDescriptor_t*);
cudnnStatus_t cudnnDestroyActivationDescriptor(cudnnActivationDescriptor_t);
cudnnStatus_t cudnnSetActivationDescriptor(cudnnActivationDescriptor_t, cudnnActivationMode_t, int, int);

#define cudnnActivationForward(x1, x2, x3, x4, x5, x6, x7, x8) cudnnActivationForward(x1, *x2, x3, x4, x5, x6, x7, x8)
#define cudnnActivationBackward(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) cudnnActivationBackward(x1, *x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)

#define cudnnSetPooling2dDescriptor(x1, x2, x3, x4, x5, x6, x7, x8, x9) cudnnSetPooling2dDescriptor(x1, x2, x4, x5, x6, x7, x8, x9)

#define cudnnSetFilter4dDescriptor(x1, x2, x3, x4, x5, x6, x7) cudnnSetFilter4dDescriptor(x1, x2, x4, x5, x6, x7)
#define cudnnConvolutionBackwardFilter(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) cudnnConvolutionBackwardFilter(x1, x2, x3, x4, x5, x6, x7, x11, x12, x13)
#define cudnnConvolutionBackwardData(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) cudnnConvolutionBackwardData(x1, x2, x3, x4, x5, x6, x7, x11, x12, x13)

#endif



