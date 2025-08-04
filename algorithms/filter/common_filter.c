/**********************************************************
 * �޷��˲��� (Clipping Filter)
 * 
 * �����ֵ���ϴ�ֵ֮��<=�޷�ֵ���򱾴�ֵ��Ч�����򱾴�ֵ��Ч
 *********************************************************/

#define MAX_DELTA 10  // �����������ֵ

int clip_filter(int new_val, int last_val) {
    if (abs(new_val - last_val) > MAX_DELTA) 
        return last_val;
    return new_val;
}


/**********************************************************
 * ��ֵ�˲��� (Clipping Filter)
 * 
 * �� N �����ݽ�������ȡ���м�ֵ��Ϊ����ֵ
 *********************************************************/

#define N 5  // �������ڴ�С

int median_filter(int samples[N]) {
    // ð������ʵ���ò����������Ч��
    for(int i=0; i<N-1; i++) {
        for(int j=0; j<N-i-1; j++) {
            if(samples[j] > samples[j+1]) {
                int temp = samples[j];
                samples[j] = samples[j+1];
                samples[j+1] = temp;
            }
        }
    }
    return samples[N/2];  // ������ֵ
}


/**********************************************************
 * ����ƽ���˲� (Moving Average)
 * 
 * �� N �����ݽ�������ƽ������Ϊ����ֵ
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
 * һ�׵�ͨ�˲� (RC Filter) / һ���ͺ��˲� (Lag Filter)
 * 
 * ����ֵ���ϴ�ֵ���м�Ȩƽ������Ϊ����ֵ
 *********************************************************/

// ������λ�棨�޸��㣩
#define SHIFT 3  // ��=1/8

int low_pass_filter(int new_sample, int last_out) {
    return last_out - (last_out >> SHIFT) + (new_sample >> SHIFT);
}

// ����棨���ȸ��ߣ�
#define ALPHA 0.2f
float rc_filter(float new_sample, float last_out) {
    return ALPHA * new_sample + (1-ALPHA) * last_out;
}


/**********************************************************
 * ��Ȩƽ�� (Weighted Average)
 * 
 * �� N �����ݽ��м�Ȩƽ������Ϊ����ֵ
 *********************************************************/

#define N 4
const int weights[N] = {1, 2, 3, 4}; // Ȩ��ϵ��

int weighted_avg(int samples[N]) {
    int sum = 0, weight_sum = 0;
    for(int i=0; i<N; i++) {
        sum += samples[i] * weights[i];
        weight_sum += weights[i];
    }
    return sum / weight_sum;
}


/**********************************************************
 * ����ƽ���˲�����Recursive Moving Average��
 * 
 * ��
 *********************************************************/
#define WINDOW_SIZE 8  // ���ڳ���

typedef struct {
    int buffer[WINDOW_SIZE];
    int index;
    long sum;
} MovingAvgFilter;

int update_moving_avg(MovingAvgFilter* filter, int new_val) {
    // �Ƴ���ֵ�������ܺ�
    filter->sum -= filter->buffer[filter->index];
    
    // �����ֵ
    filter->buffer[filter->index] = new_val;
    filter->sum += new_val;
    
    // �������������λ�������
    filter->index = (filter->index + 1) % WINDOW_SIZE;
    
    // ����ƽ��ֵ������������
    return (int)(filter->sum / WINDOW_SIZE);
}

// ��ʼ��ʾ��
MovingAvgFilter temp_filter = {0};






/**************** �������˲� (Kalman Filter) ****************/  
typedef struct {
    float q;  // ��������
    float r;  // ��������
    float x;  // ״ֵ̬
    float p;  // �������
} Kalman;

float kalman_update(Kalman* k, float measurement) {
    // Ԥ��
    k->p = k->p + k->q;
    
    // ����
    float kg = k->p / (k->p + k->r); // ����������
    k->x = k->x + kg * (measurement - k->x);
    k->p = (1 - kg) * k->p;
    
    return k->x;
}
/**************** �������˲� (Kalman Filter) ****************/   


/**************** ��������ֵ�˲� (Min-Max Filter) **********/
#define N 5

int min_max_filter(int samples[N]) {
    int min = samples[0], max = samples[0];
    long sum = samples[0];
    
    // �Ҽ�ֵ�����
    for(int i=1; i<N; i++) {
        if(samples[i] < min) min = samples[i];
        if(samples[i] > max) max = samples[i];
        sum += samples[i];
    }
    
    return (sum - min - max) / (N - 2); // �޳���ֵ��ƽ��
}
/**************** ��������ֵ�˲� (Min-Max Filter) **********/

/**********************************************************
 * 
 * 
 * 
 *********************************************************/