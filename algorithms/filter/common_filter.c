/**********************************************************
 * 限幅滤波法 (Clipping Filter)
 * 
 * 如果新值与上次值之差<=限幅值，则本次值有效，否则本次值无效
 *********************************************************/

#define MAX_DELTA 10  // 最大允许跳变值

int clip_filter(int new_val, int last_val) {
    if (abs(new_val - last_val) > MAX_DELTA) 
        return last_val;
    return new_val;
}


/**********************************************************
 * 中值滤波法 (Clipping Filter)
 * 
 * 对 N 个数据进行排序，取出中间值作为本次值
 *********************************************************/

#define N 5  // 采样窗口大小

int median_filter(int samples[N]) {
    // 冒泡排序（实际用插入排序更高效）
    for(int i=0; i<N-1; i++) {
        for(int j=0; j<N-i-1; j++) {
            if(samples[j] > samples[j+1]) {
                int temp = samples[j];
                samples[j] = samples[j+1];
                samples[j+1] = temp;
            }
        }
    }
    return samples[N/2];  // 返回中值
}


/**********************************************************
 * 算术平均滤波 (Moving Average)
 * 
 * 对 N 个数据进行算术平均，作为本次值
 *********************************************************/

#define N 8
int buffer[N];
int idx = 0;

int moving_avg(int new_sample) {
    buffer[idx] = new_sample;
    idx = (idx + 1) % N;
    
    long sum = 0;
    for(int i=0; i<N; i++) sum += buffer[i];
    
    return (int)(sum / N);
}


/**********************************************************
 * 一阶低通滤波 (RC Filter) / 一阶滞后滤波 (Lag Filter)
 * 
 * 将新值与上次值进行加权平均，作为本次值
 *********************************************************/

// 整数移位版（无浮点）
#define SHIFT 3  // α=1/8

int low_pass_filter(int new_sample, int last_out) {
    return last_out - (last_out >> SHIFT) + (new_sample >> SHIFT);
}

// 浮点版（精度更高）
#define ALPHA 0.2f
float rc_filter(float new_sample, float last_out) {
    return ALPHA * new_sample + (1-ALPHA) * last_out;
}


/**********************************************************
 * 加权平均 (Weighted Average)
 * 
 * 将 N 个数据进行加权平均，作为本次值
 *********************************************************/

#define N 4
const int weights[N] = {1, 2, 3, 4}; // 权重系数

int weighted_avg(int samples[N]) {
    int sum = 0, weight_sum = 0;
    for(int i=0; i<N; i++) {
        sum += samples[i] * weights[i];
        weight_sum += weights[i];
    }
    return sum / weight_sum;
}


/**********************************************************
 * 递推平均滤波法（Recursive Moving Average）
 * 
 * 将
 *********************************************************/
#define WINDOW_SIZE 8  // 窗口长度

typedef struct {
    int buffer[WINDOW_SIZE];
    int index;
    long sum;
} MovingAvgFilter;

int update_moving_avg(MovingAvgFilter* filter, int new_val) {
    // 移除旧值并更新总和
    filter->sum -= filter->buffer[filter->index];
    
    // 添加新值
    filter->buffer[filter->index] = new_val;
    filter->sum += new_val;
    
    // 更新索引（环形缓冲区）
    filter->index = (filter->index + 1) % WINDOW_SIZE;
    
    // 返回平均值（整数除法）
    return (int)(filter->sum / WINDOW_SIZE);
}

// 初始化示例
MovingAvgFilter temp_filter = {0};






/**************** 卡尔曼滤波 (Kalman Filter) ****************/  
typedef struct {
    float q;  // 过程噪声
    float r;  // 测量噪声
    float x;  // 状态值
    float p;  // 估计误差
} Kalman;

float kalman_update(Kalman* k, float measurement) {
    // 预测
    k->p = k->p + k->q;
    
    // 更新
    float kg = k->p / (k->p + k->r); // 卡尔曼增益
    k->x = k->x + kg * (measurement - k->x);
    k->p = (1 - kg) * k->p;
    
    return k->x;
}
/**************** 卡尔曼滤波 (Kalman Filter) ****************/   


/**************** 滑动窗格极值滤波 (Min-Max Filter) **********/
#define N 5

int min_max_filter(int samples[N]) {
    int min = samples[0], max = samples[0];
    long sum = samples[0];
    
    // 找极值并求和
    for(int i=1; i<N; i++) {
        if(samples[i] < min) min = samples[i];
        if(samples[i] > max) max = samples[i];
        sum += samples[i];
    }
    
    return (sum - min - max) / (N - 2); // 剔除极值后平均
}
/**************** 滑动窗格极值滤波 (Min-Max Filter) **********/

/**********************************************************
 * 
 * 
 * 
 *********************************************************/