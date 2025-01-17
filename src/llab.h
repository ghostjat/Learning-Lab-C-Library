/*
MIT License

Copyright (c) 2018 Viviano Riccardo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files ((the "LICENSE")), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __LLAB_H__
#define __LLAB_H__

#ifdef _WIN32
typedef unsigned int uint;
#else
//typedef unsigned int uint;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>

#define N_NORMALIZATION 5
#define BETA_NORMALIZATION 0.75
#define ALPHA_NORMALIZATION 0.0001
#define K_NORMALIZATION 2

#define NESTEROV 1
#define ADAM 2
#define RADAM 3
#define DIFF_GRAD 4
#define ADAMOD 5

//actions in model / struct conn transf
#define FCLS 1
#define CLS 2
#define RLS 3
#define BNS 4
#define LSTMS 5
#define TRANSFORMER_ENCODER 6
#define TRANSFORMER_DECODER 7
#define TRANSFORMER 8
#define MODEL 9
#define RMODEL 10
#define ATTENTION 11
#define MULTI_HEAD_ATTENTION 12
#define L2_NORM_CONN 13
#define VECTOR 14
#define NOTHING 15
#define TEMPORAL_ENCODING_MODEL 16

// activations
#define NO_ACTIVATION 0
#define SIGMOID 1
#define RELU 2
#define SOFTMAX 3
#define TANH 4
#define LEAKY_RELU 5
#define ELU 6

//pooling (2d)
#define NO_POOLING 0
#define MAX_POOLING 1
#define AVERAGE_POOLING 2

//dropout
#define NO_DROPOUT 0
#define DROPOUT 1
#define DROPOUT_TEST 2

//normalizations
#define NO_NORMALIZATION 0
#define LOCAL_RESPONSE_NORMALIZATION 1//implemented inside convolutional layer
#define BATCH_NORMALIZATION 2// not implemented inside any layer 
#define GROUP_NORMALIZATION 3// implemented only for lstm, convolutional, can be seen as layer_normalization if n_groups = 1
#define LAYER_NORMALIZATION 4// implemented only for fully connected
#define SCALED_L2_NORMALIZATION 5 // not implemented inside fully connected and neither convolutional
#define COSINE_NORMALIZATION 6 // must be added

//optimization algorithms hyperparameters
#define BETA1_ADAM 0.9
#define BETA2_ADAM 0.999
#define BETA3_ADAMOD 0.9999
#define EPSILON_ADAM 1e-7
#define EPSILON 1e-7
#define RADAM_THRESHOLD 4

//regularization in update
#define NO_REGULARIZATION 0
#define L2_REGULARIZATION 1

//convolution
#define NO_CONVOLUTION 1
#define CONVOLUTION 2
#define TRANSPOSED_CONVOLUTION 3

//useless for now
#define BATCH_NORMALIZATION_TRAINING_MODE 1
#define BATCH_NORMALIZATION_FINAL_MODE 2

//useless for now
#define STATEFUL 1
#define STATELESS 2

//activation thresholds
#define LEAKY_RELU_THRESHOLD 0.1
#define ELU_THRESHOLD 1

//lstm residual or not
#define LSTM_RESIDUAL  1
#define LSTM_NO_RESIDUAL 0

//transformer residual or not
#define TRANSFORMER_RESIDUAL 1
#define TRANSFORMER_NO_RESIDUAL 0 

//loss
#define NO_SET -1
#define NO_LOSS 0
#define CROSS_ENTROPY_LOSS 1 << 0
#define FOCAL_LOSS 1 << 1
#define HUBER1_LOSS 1 << 2
#define HUBER2_LOSS 1 << 3
#define MSE_LOSS 1 << 4
#define KL_DIVERGENCE_LOSS 1 << 5
#define ENTROPY_LOSS 1 << 6
#define TOTAL_VARIATION_LOSS_2D 1 << 7
#define CONTRASTIVE_2D_LOSS 1 << 8

//look ahead algorithm hyperparameters
#define LOOK_AHEAD_ALPHA 0.8
#define LOOK_AHEAD_K 10

//training modes and feed forward flag
#define GRADIENT_DESCENT 1 //training_mode
#define EDGE_POPUP 2//training mode - feed_forward_flag
#define FULLY_FEED_FORWARD 3//feed_forward_flag
#define FREEZE_TRAINING 4//training_mode
#define FREEZE_BIASES 5//training_mode
#define ONLY_FF 6//feed_forward_flag

#define ONLY_DROPOUT 5//feed_forward_flag (only fully-connected)

//attention types
#define STANDARD_ATTENTION 1
#define MASKED_ATTENTION 2

//for decoders
#define RUN_ONLY_DECODER 0
#define RUN_ONLY_ENCODER 1
#define RUN_ALL_TRANSF 2

// for sort algorithm at the end of each edge popup iteration
#define SORT_SWITCH_THRESHOLD 1e6// used to sort the scores if > of this threshold bottom up merge sort is used, otherwise quicksort is used

//vector
#define NO_ACTION 0
#define ADDITION 1 
#define SUBTRACTION 2 
#define MULTIPLICATION 3
#define RESIZE 4
#define CONCATENATE 5
#define DIVISION 6
#define INVERSE 7
#define CHANGE_SIGN 8
#define GET_MAX 9
#define NO_CONCATENATE 10

#define POSITIONAL_ENCODING 13

// Neat hyperparams
#define SPECIES_THERESHOLD 3 // parameter for specie distance
#define INITIAL_POPULATION 100
#define GENERATIONS 600000
#define PERCENTAGE_SURVIVORS_PER_SPECIE 0.3 //the number of specie survivors is decided by the fitness of the specie/mean fitness * children param, but the genomes taken to reproduce are the best <PERCENTAGE_SURVIVORS_PER_SPECIE>
#define CONNECTION_MUTATION_RATE 0.8
#define NEW_CONNECTION_ASSIGNMENT_RATE 0.1
#define ADD_CONNECTION_BIG_SPECIE_RATE 0.3
#define ADD_CONNECTION_SMALL_SPECIE_RATE 0.03
#define ADD_NODE_SPECIE_RATE 0.05
#define ACTIVATE_CONNECTION_RATE 0.25//there is activate_connection_rate% that a connetion remains disabled
#define REMOVE_CONNECTION_RATE 0.01//there is remove_connection_rate% that a connection can be removed
#define CHILDREN 1//new offsprings = children*(round_up(b*3.67)) where b is mean fitness specie/mean fitness population
#define CROSSOVER_RATE 0.1 
#define SAVING 10//each <saving> generation the best genomes is saved
#define LIMITING_SPECIES 15 // if a specie fitness is under the avarage of the population or the fitness doesn't increase for limiting_species generations, just kill it
#define LIMITING_THRESHOLD 5// if a specie fitness is under the avarage of the population or the fitness doesn't increase for limiting_species-limiting_threshold generations, we invert the trend of the specie with adding/removing connection
#define MAX_POPULATION 4000 // the population is cut everytime it exceeds max population param
#define SAME_FITNESS_LIMIT 10
#define AGE_SIGNIFICANCE 0.3// the age significance param affects the mean fitness of a specie according to the age of the specie itself

#define PI 3.14159265358979323846


#define LR_NO_DECAY 0
#define LR_CONSTANT_DECAY 1
#define LR_TIME_BASED_DECAY 2
#define LR_STEP_DECAY 3
#define LR_ANNEALING_DECAY 4

#define UNIFORM_SAMPLING 1
#define RANKED_SAMPLING 2
#define REWARD_SAMPLING 3

typedef struct bn{//batch_normalization layer
    int batch_size, vector_dim;
    float epsilon;
    float** input_vectors;//batch_size*vector_dim
    float** temp_vectors;//batch_size*vector_dim
    float* gamma;//vector_dim
    float* d_gamma;//vector_dim
    float* d1_gamma;//vector_dim
    float* d2_gamma;//vector_dim
    float* d3_gamma;//vector_dim
    float* beta;//vector_dim
    float* d_beta;//vector_dim
    float* d1_beta;//vector_dim
    float* d2_beta;//vector_dim
    float* d3_beta;//vector_dim
    float* mean;//vector_dim
    float* var;//vector_dim
    float** outputs;//batch_size*vector_dim
    float** error2;//batch_size*vector_dim
    float** temp1;//batch_size*vector_dim, for bp
    float* temp2;//vector_dim, for bp
    int training_mode;//GRADIENT_DESCENT, FREEZE_TRAINING
}bn;


/* LAYERS MUST START FROM 0*/
typedef struct fcl { //fully-connected-layers
    int input,output,layer,dropout_flag, normalization_flag;//dropout flag = 1 if dropout must be applied
    int activation_flag; // activation flag = 0 -> no activation, flag = 1 -> sigmoid, = 2 -> relu, = 3 -> softmax, 4->tanhh
    int training_mode,feed_forward_flag, n_groups;//GRADIENT_DESCENT, EDGE_POPUP, FREEZE_TRAINING
    float* weights;// output*input
    float* d_weights;// output*input
    float* d1_weights;// output*input
    float* d2_weights;// output*input
    float* d3_weights;// output*input
    float* biases; //output
    float* d_biases; //output
    float* d1_biases; //output
    float* d2_biases; //output
    float* d3_biases; //output
    float* pre_activation; //output
    float* post_activation; //output
    float* post_normalization; //output
    float* dropout_mask;//output
    float* dropout_temp;//output
    float* temp;//output
    float* temp3;//output
    float* temp2;//input
    float* error2;//input
    float dropout_threshold;
    float k_percentage;// for edge-popup algorithm
    int n_best_w;// for edge-popup algorithm
    int* indices;// for edge-popup algorithm, output*input
    int* active_output_neurons;// for edge-popup algorithm, output
    float* scores;//for edge-popup algorithm,output*input
    float* d_scores;//for edge-popup algorithm,output*input
    float* d1_scores;//for edge-popup algorithm,output*input
    float* d2_scores;//for edge-popup algorithm,output*input
    float* d3_scores;//for edge-popup algorithm,output*input
    bn* layer_norm;
    
    
} fcl;

/* PADDING_ROWS MUST BE = PADDING_COLS AND ALSO STRIDE_ROWS = STRIDE_COLS*/
typedef struct cl { //convolutional-layers
    int channels, input_rows, input_cols,layer, convolutional_flag;
    int kernel_rows, kernel_cols, n_kernels;
    int stride1_rows, stride1_cols, padding1_rows, padding1_cols;
    int stride2_rows, stride2_cols, padding2_rows, padding2_cols;
    int pooling_rows, pooling_cols;
    int normalization_flag, activation_flag, pooling_flag; // activation flag = 0, no activation, = 1 sigmoid, = 2 relu, pooling flag = 1 max-pooling, = 2 avarage-pooling
    int rows1, cols1, rows2,cols2;
    int group_norm_channels;
    int training_mode,feed_forward_flag;//GRADIENT_DESCENT, EDGE_POPUP
    int* used_kernels; //k_kernels, 1 where the kernel is used, 0 otherwise
    float** kernels; //n_kernels - channels*kernel_rows*kernel_cols
    float** d_kernels; //n_kernels - channels*kernel_rows*kernel_cols
    float** d1_kernels; //n_kernels - channels*kernel_rows*kernel_cols
    float** d2_kernels; //n_kernels - channels*kernel_rows*kernel_cols
    float** d3_kernels; //n_kernels - channels*kernel_rows*kernel_cols
    float* biases; //n_kernels
    float* d_biases; //n_kernels
    float* d1_biases; //n_kernels
    float* d2_biases; //n_kernels
    float* d3_biases; //n_kernels
    float* pre_activation;//n_kernels*((input_rows-kernel_rows)/stride1_rows +1 + 2*padding1_rows)*((input_cols-kernel_cols)/stride1_cols +1 + 2*padding1_cols) or n_kernels*((input_rows-1)*stride1_rows+kernel_rows - 2*padding1_rows)*((input_cols-1)*stride1_cols+kernel_cols - 2*padding1_cols)
    float* post_activation;//n_kernels*((input_rows-kernel_rows)/stride1_rows +1 + 2*padding1_rows)*((input_cols-kernel_cols)/stride1_cols +1 + 2*padding1_cols) or n_kernels*((input_rows-1)*stride1_rows+kernel_rows - 2*padding1_rows)*((input_cols-1)*stride1_cols+kernel_cols - 2*padding1_cols)
    float* post_normalization;//n_kernels*((input_rows-kernel_rows)/stride1_rows +1 + 2*padding1_rows)*((input_cols-kernel_cols)/stride1_cols +1 + 2*padding1_cols) or n_kernels*((input_rows-1)*stride1_rows+kernel_rows - 2*padding1_rows)*((input_cols-1)*stride1_cols+kernel_cols - 2*padding1_cols)
    float* post_pooling;//n_kernels*(((rows1 - pooling_rows)/stride2_rows + 1 + 2*padding2_rows)*((cols1 - pooling_cols)/stride2_cols + 1 + 2*padding2_cols)
    float* temp;//n_kernels*rows1*cols1
    float* temp2;//n_kernels*rows1*cols1
    float* temp3;//n_kernels*rows1*cols1
    float* pooltemp;//channels*input_rows*input_cols
    float* error2;//channels*input_rows*input_cols
    bn** group_norm;//n_kernels/group_norm_channels
    float k_percentage;// for edge-popup algorithm
    int n_best_w;// for edge-popup algorithm
    int* indices;// for edge-popup algorithm, n_kernels*channels*kernel_rows*kernel_cols
    float* scores;//for edge-popup algorithm,n_kernels*channels*kernel_rows*kernel_cols
    float* d_scores;//for edge-popup algorithm,n_kernels*channels*kernel_rows*kernel_cols
    float* d1_scores;//for edge-popup algorithm,n_kernels*channels*kernel_rows*kernel_cols
    float* d2_scores;//for edge-popup algorithm,n_kernels*channels*kernel_rows*kernel_cols
    float* d3_scores;//for edge-popup algorithm,n_kernels*channels*kernel_rows*kernel_cols
    
} cl;

typedef struct rl { //residual-layers
    int channels, input_rows, input_cols, n_cl;
    float* input;
    cl* cl_output;
    cl** cls;
} rl;

typedef struct lstm { //long short term memory layers
    int input_size, output_size, layer,dropout_flag_up;
    int dropout_flag_right, window, residual_flag; 
    int norm_flag, n_grouped_cell;//dropout flag = 1 if dropout must be applied
    int training_mode, feed_forward_flag;
    float** w;// 4 x size*size
    float** u;// 4 x size*size
    float** d_w;// 4 x size*size
    float** d1_w;// 4 x size*size
    float** d2_w;// 4 x size*size
    float** d3_w;// 4 x size*size
    float** d_u;// 4 x size*size
    float** d1_u;// 4 x size*size
    float** d2_u;// 4 x size*size
    float** d3_u;// 4 x size*size
    float** biases; //4 x size
    float** d_biases; //4 x size
    float** d1_biases; //4 x size
    float** d2_biases; //4 x size
    float** d3_biases; //4 x size
    int** w_active_output_neurons;// for edge-popup algorithm, output, 4 x size
    int** u_active_output_neurons;// for edge-popup algorithm, output, 4 x size
    int** w_indices;//4 x size*size
    int** u_indices;//4 x size*size
    float** w_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** u_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** d_w_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** d_u_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** d1_w_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** d1_u_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** d2_w_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** d2_u_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** d3_w_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float** d3_u_scores;//for edge-popup algorithm,output*input, 4 x size*size
    float*** lstm_z; //window x 4 x size
    float** lstm_hidden; //window x size
    float** lstm_cell; //window x size
    float* dropout_mask_up;//size
    float* dropout_mask_right;//size
    float** out_up;//window x size
    float dropout_threshold_up;
    float dropout_threshold_right;
    float k_percentage;
    bn** bns;//window/n_grouped_cell
} lstm;

typedef struct model {
    int layers, n_rl, n_cl, n_fcl,error_flag,output_dimension;
    float error_threshold1;
    float error_threshold2;
    float beta1_adam;
    float beta2_adam;
    float beta3_adamod;
    float error_gamma;
    float* error_alpha;
    float* error;
    rl** rls;//rls = residual-layers
    cl** cls;//cls = convolutional-layers
    fcl** fcls; // fcls = fully-connected-layers
    int** sla; //layers*layers, 1 for fcls, 2 for cls, 3 for rls, sla = sequential layers array
    float* output_layer;// will be the last array
} model;

typedef struct rmodel {
    int layers, n_lstm, window, hidden_state_mode, error_flag, output_dimension;
    float error_threshold1;
    float error_threshold2;
    float beta1_adam;
    float beta2_adam;
    float beta3_adamod;
    float error_gamma;
    float** error_alpha;
    float** error;
    lstm** lstms;
    int** sla;
} rmodel;

typedef struct recurrent_enc_dec {
    rmodel* encoder;
    rmodel* decoder;
    model** m;//decoder->window
    float beta1_adam;
    float beta2_adam;
    float beta3_adamod;
    float* flatten_fcl_input;//encoder->size*(encoder->window+1)
    float** output_encoder;//encoder->window x encoder->size
    float** hiddens;//decoder->window x encoder->size
    float** output_error_encoder;//encoder->window x decoder->size
    float** softmax_array;//decoder->window x encoder->window
}recurrent_enc_dec;

typedef struct vaemodel{
    int latent_size;
    float* z;
    float* input;
    float* dmean;
    float* dstd;
    model* encoder;// last layer must be sizze = latent_space*2
    model* decoder;
} vaemodel;

typedef struct scaled_l2_norm{
    int input_dimension, training_mode;
    float* output;
    float* output_error;
    float norm;
    float learned_g;
    float d_learned_g;
    float d1_learned_g;
    float d2_learned_g;
    float d3_learned_g;
    float ex_d_learned_g_diff_grad;
}scaled_l2_norm;

typedef struct transformer_encoder{
    int input_dimension,n_head,attention_flag,residual_flag1,normalization_flag1,dimension, k_embedding_dimension, v_embedding_dimension; 
    int residual_flag2,normalization_flag2, n_l2; 
    scaled_l2_norm** l2;//2 or 1 or 0
    fcl** fcls;// 3*n_head
    model* m;//the model after the attention + possible residual and normalization
    model* linear_after_attention;
    float* encoder_output_error;//m->output_dimension
    model** q;//n_head
    model** k;//n_head
    model** v;//n_head
    float* q_error;//n_head X q[i] otuput_dimension
    float* k_error;//n_head X k[i] otuput_dimension
    float* v_error;//n_head X v[i] otuput_dimension
    float* score_matrix;//n_head X dimension X dimension(input_dimension/n_head)
    float* score_matrix_error;//n_head X dimension X dimension(input_dimension/n_head)
    float* score_matrix_softmax;//n_head X dimension X dimension(input_dimension/n_head)
    float* score_matrix_softmax_error;//n_head X dimension X dimension(input_dimension/n_head)
    float* attention_output;//input_dimension (n_head*dimension)
    float* residual1_output;//input_dimension
    float* residual2_output;//input_dimension
    float* residual1_output_error;//input_dimension
    float* residual2_output_error;//input_dimension
     
}transformer_encoder;

typedef struct transformer_decoder{
    int input_dimension, left_dimension, n_head,attention_flag,residual_flag,normalization_flag,dimension, encoder_input_dimension, n_l2,k_embedding,v_embedding; 
    transformer_encoder* e;//1
    model* linear_after_attention;
    scaled_l2_norm** l2;// 3 or 2 or 1 or 0
    fcl** fcls;// 3*n_head1 + 3*n_head2
    float* incoming_input;//left_dimension
    float* incoming_input_error;//left_dimension
    model** q;//n_head
    model** k;//n_head
    model** v;//n_head
    float* q_error;//n_head X q[i] otuput_dimension
    float* k_error;//n_head X k[i] otuput_dimension
    float* v_error;//n_head X v[i] otuput_dimension
    float* score_matrix;//n_head X dimension X dimension(input_dimension/n_head)
    float* score_matrix_error;//n_head X dimension X dimension(input_dimension/n_head)
    float* score_matrix_softmax;//n_head X dimension X dimension(input_dimension/n_head)
    float* score_matrix_softmax_error;//n_head X dimension X dimension(input_dimension/n_head)
    float* attention_output;//input_dimension (n_head*dimension)
    float* residual1_output;//input_dimension
    float* residual1_output_error;//input_dimension
     
}transformer_decoder;

typedef struct transformer{
    int n_te, n_td;
    float beta1_adam;
    float beta2_adam;
    float beta3_adamod;
    int** encoder_decoder_connections;//matrix of dimension: n_te X n_td
    transformer_encoder** te;
    transformer_decoder** td;
     
}transformer;

typedef struct thread_args_model {
    model* m;
    model* real_m;
    int rows,cols,channels,error_dimension;
    float* input;
    float* error;
    float** returning_error;
} thread_args_model;



typedef struct thread_args_models {
    model** m;
    int n,depth;
} thread_args_models;


typedef struct thread_args_rmodel {
    rmodel* m;
    rmodel* m2;
    float** hidden_states;
    float** cell_states;
    float** input_model;
    float** error_model;
    float**** returning_error;
    float*** ret_input_error;
} thread_args_rmodel;

typedef struct thread_args_enc_dec_model {
    recurrent_enc_dec* m;
    float** hidden_states;
    float** cell_states;
    float** input_model1;
    float** input_model2;
    float** error_model;
    float**** returning_error;
    float*** ret_input_error1;
    float*** ret_input_error2;
} thread_args_enc_dec_model;

typedef struct thread_args_vae_model {
    vaemodel* vm;
    int rows,cols,channels,error_dimension;
    float* input;
    float* error;
    float** returning_error;
} thread_args_vae_model;

typedef struct thread_args_transformer_encoder {
    transformer_encoder* t;
    float* input;
    float* error;
    float** returning_error;
    int input_size;
} thread_args_transformer_encoder;

typedef struct thread_args_transformer_decoder {
    transformer_decoder* t;
    float* input1;
    float* input2;
    float* error;
    float* returning_error2;
    float** returning_error1;
    int input_size1,input_size2;
} thread_args_transformer_decoder;

typedef struct thread_args_transformer {
    transformer* t;
    float* input_encoder;
    float* input_decoder;
    float* error;
    float** returning_error;
    int input_size1,input_size2, flag;
} thread_args_transformer;

typedef struct thread_args_server {
    int idx,client_desc, reading_pipe, writing_pipe,buffer_size;
    struct sockaddr_in* client_addr;
} thread_args_server;

typedef struct ddpg {
    int batch_size,regularization1,regularization2,n_weights1,n_weights2,index,m1_input,m1_output,m2_output,m3_output;
    int gradient_descent_flag1, gradient_descent_flag2,threads,max_frames,buff_size;
    float lr1,lr2,momentum1,momentum2,lambda1,lambda2,epsilon_greedy,lambda,tau;
    long long unsigned int t1, t2;
    model* m1;
    model* m2;
    model* m3;
    model* m4;
    model** tm1;
    model** tm2;
    model** tm3;
    model** tm4;
    model** bm1;
    model** bm2;
    model** bm3;
    model** bm4;
    float** buff1;
    float** buff2;
    float* rewards;
    float** actions;
    int* terminal;
    float** tm1_output_array;
    float** tm2_output_array;
    float** tm3_output_array;
    float** tm4_output_array;
    float** bm1_output_array;
    float** bm2_output_array;
    float** bm3_output_array;
} ddpg;

typedef struct oustrategy {
    int action_dim;
    float mu,theta,sigma,max_sigma,min_sigma;
    float* action_max;
    float* action_min;
    long long unsigned int decay_period;
    float* state;
    float* action_space;
} oustrategy;



// Generic dictionary for int vectors
typedef struct mystruct{
    struct mystruct* brother;
    struct mystruct* son;
    int c;
}mystruct;

typedef struct training{
    model** m;
    rmodel** r;
    int epochs,instance,n_char_size,n_int_size,n_float_size,n_m, n_r, n_float, n_int, n_char;
    char** chars;
    int** ints;
    float** floats;
}training;




typedef struct vector_struct{
    float* v, *output, *input_error;
    int action,v_size, output_size, activation_flag, dropout_flag, index, input_size;
    float dropout_threshold;
}vector_struct;

typedef struct struct_conn{
    int id, concatenate_flag;
    model** temporal_m;//temporal_encoding_model_size
    model** temporal_m2;//used only in case of concatenate (must be assigned by a previous other already allocated temporal_m)
    model* m1, *m2;
    rmodel* r1, *r2;
    transformer_encoder* e1, *e2;
    transformer_decoder* d1, *d2;
    transformer* t1, *t2;
    scaled_l2_norm* l1, *l2;
    vector_struct* v1, *v2, *v3;
    int input1_type, input2_type, output_type;//model, rmodel, encoder transf, decoder transf, transf
    int decoder_left_input, decoder_down_input, transf_dec_input, transf_enc_input;//transf_enc_input is used either for the transformer or for the encoder
    int model_input_index, temporal_encoding_model_size, input_size;//all for models, model_input_index is used also for l2 normalization and vector for the input1type and also for vector respect input1_type
    int vector_index;//used in case of concatenate for input2_type
    
    //rmodel
    int* rmodel_input_left;//r2->n_lstm
    int* rmodel_input_down;//r2->lstms[0]->window
    
    //temporal m
    int* input_temporal_index;//temporal_encoding_model_size
    
    //encoder
    int* input_encoder_indeces;//transf_enc_input
    
    //decoder
    int* input_decoder_indeces_left;//decoder_left_input
    int* input_decoder_indeces_down;//decoder_down_input
    
    // transformer
    int* input_transf_encoder_indeces;//transf_enc_input
    int* input_transf_decoder_indeces;//transf_dec_input
    
    // rmodel
    float** h;//left for rmodel
    float** c;//left for rmodel
    float** inputs;// down input for rmodel (r2)
    
    //encoder
    float* encoder_input;//transf_enc_input
    
    //decoder
    float* decoder_input_left;//decoder_left_input
    float* decoder_input_down;//decoder_down_input
    
    //transformer
    float* transformer_input_encoder;//decoder_left_input
    float* transformer_input_decoder;//decoder_down_input
    
}struct_conn;


typedef struct struct_conn_handler{
    int visited,struct_type_flag,error_flag,n_inputs,n_outputs,id,depth;
    vector_struct* input;
    struct struct_conn_handler** inputs;
    struct struct_conn_handler** outputs;
    vector_struct* output;
    float lambda;
    float huber1;
    float huber2;
    float* alpha;
    model* m;
    rmodel* r;
    transformer_encoder* e;// for now just model rmodel and transformer encoder
    vector_struct* v;
    scaled_l2_norm* l2;
}struct_conn_handler;

typedef struct error_handler{
    int size,reference_index;
    int free_flag_error;
    float* ret_error;
}error_handler;

typedef struct error_super_struct{
    int n_error_handlers;
    error_handler** e;
}error_super_struct;

typedef struct dueling_categorical_dqn{
    int input_size;
    int action_size;
    int n_atoms;
    float v_max, v_min, z_delta;
    model* shared_hidden_layers;
    model* v_hidden_layers;
    model* a_hidden_layers;
    model* v_linear_last_layer;
    model* a_linear_last_layer;
    float* action_mean_layer;//n_atoms
    float* add_layer;//actions_size X n_atoms
    float* softmax_layer;//action_size X n_atoms
    float* derivative_softmax_layer;//action_size X n_atoms
    float* v_linear_layer_error;//n_atoms
    float* a_linear_layer_error;//action_size X n_atoms
    float* support;//n_atoms
    float* error;//action_size X n_atoms
    float* q_functions;//action_size
    
}dueling_categorical_dqn;


typedef struct thread_args_dueling_categorical_dqn_train {
    dueling_categorical_dqn *online_net, *online_net_wlp, *target_net, *target_net_wlp;
    int input_size;
    float* state_t;
    float* q_functions;
    float reward_t;
    float* state_t_1;
    float* new_error;
    float weighted_error;
    int action_t;
    int nonterminal_s_t_1;
    int state_sizes;
    float lambda;
    float weight;
    float clip;
    float alpha;
    float* ret;
} thread_args_dueling_categorical_dqn_train;

typedef struct thread_args_dueling_categorical_dqn {
    dueling_categorical_dqn** m;
    int n,depth;
} thread_args_dueling_categorical_dqn;



typedef struct rainbow{
    float max_epsilon, min_epsilon, epsilon_decay, epsilon, alpha_priorization, beta_priorization, lambda_value, tau_copying, momentum, gamma;// lambda for n step, gamma for dqn error
    float beta1, beta2, beta3, k_percentage, clipping_gradient_value, adaptive_clipping_gradient_value, diversity_driven_threshold, alpha, beta_priorization_increase;
    float lr, lr_minimum, lr_maximum, initial_lr, lr_decay, diversity_driven_decay, diversity_driven_minimum, diversity_driven_maximum;
    float** buffer_state_t;// not stored terminal states
    float** buffer_state_t_1;
    int* nonterminal_state_t_1;
    int* actions;
    float* rewards;
    float* ranked_values;
    float* recursive_cumulative_ranked_values;
    int* positive_ranked_values;
    float* positive_recursive_cumulative_ranked_values;
    int* negative_ranked_values;
    float* negative_recursive_cumulative_ranked_values;
    int* neutral_ranked_values;
    float* neutral_recursive_cumulative_ranked_values;
    float* diversity_driven_q_functions_buffer;
    float** diversity_driven_states;
    float* last_errors_dqn;
    float* last_errors_diversity_driven;
    int* uniform_sampling_indices;
    int* positive_rewards;
    int* negative_rewards;
    int* neutral_rewards;
    int* positive_reverse_indices;
    int* negative_reverse_indices;
    int* neutral_reverse_indices;
    dueling_categorical_dqn* online_net;
    dueling_categorical_dqn* target_net;
    dueling_categorical_dqn** online_net_wlp;
    dueling_categorical_dqn** target_net_wlp;
    float* error_priorization;
    int* error_indices;
    int* reverse_error_indices;// for debug
    int feed_forward_flag, training_mode, clipping_flag, adaptive_clipping_flag, batch_size, threads, gd_flag, lr_decay_flag, sampling_flag;
    double sum_error_priorization_buffer;
    double positive_sum_error_priorization_buffer;
    double negative_sum_error_priorization_buffer;
    double neutral_sum_error_priorization_buffer;
    uint64_t action_taken_iteration, max_buffer_size, train_iteration, buffer_current_index, n_step_rewards, stop_epsilon_greedy,epochs_to_copy_target, diversity_driven_q_functions, lr_epoch_threshold;
    uint64_t diversity_driven_q_functions_counter,past_errors_counter, past_errors, positive_rewards_counter, negative_rewards_counter, neutral_rewards_counter;
    uint64_t positive_rewards_length, negative_rewards_length, neutral_rewards_length;// past_errors, for softadaptù
    
    
    // during training
    int* array_to_shuffle;
    uint* batch;
    uint* negative_batch, *positive_batch, *neutral_batch;
    uint* reverse_batch;
    float** temp_states_t;
    float** temp_states_t_1;
    float** temp_diversity_states_t;
    float** qs;
    int* temp_nonterminal_state_t_1;
    int* temp_actions;
    float* temp_rewards;
    float* new_errors;
    float* weighted_errors;
    
}rainbow;


#include "attention.h"
#include "batch_norm_layers.h"
#include "clipping_gradient.h"
#include "convolutional.h"
#include "convolutional_layers.h"
#include "dictionary.h"
#include "drl.h"
#include "dueling_categorical_dqn.h"
#include "fully_connected.h"
#include "fully_connected_layers.h"
#include "gd.h"
#include "initialization.h"
#include "learning_rate_decay.h"
#include "math_functions.h"
#include "model.h"
#include "multi_core_dueling_categorical_dqn.h"
#include "multi_core_model.h"
#include "multi_core_neat.h"
#include "multi_core_rmodel.h"
#include "multi_core_vae_model.h"
#include "neat_functions.h"
#include "normalization.h"
#include "parser.h"
#include "rainbow.h"
#include "recurrent.h"
#include "recurrent_layers.h"
#include "regularization.h"
#include "residual_layers.h"
#include "rmodel.h"
#include "positional_encoding.h"
#include "scaled_l2_norm_layers.h"
#include "struct_conn.h"
#include "struct_conn_handler.h"
#include "training.h"
#include "transformer.h"
#include "transformer_decoder.h"
#include "transformer_encoder.h"
#include "update.h"
#include "utils.h"
#include "vae_model.h"
#include "vector.h"

#endif
