//
// Created by Administrator on 2020/5/14.
//

#include<bits/stdc++.h>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
struct Node{
    uint32_t to{};
    float je{};
    Node()= default;
    void set(uint32_t &a, float &b){
        to =a;
        je =b;
    }
    Node(const Node &nd){//拷贝构造函数
        to = nd.to;
        je = nd.je;
    }
};
//#define TEST
#define JEJUDGE
#define JEJUDGE_REVERSE
#define INMAX 16
#define OUTMAX 16
const float MINJE = 0.2;
const float MAXJE = 3.0;
const int MAX_E=2000000;
#define THREAD_NUM 4
#define CS 0.3
#define MAXSIZE8 1024 * 1024 * 800
#define MAXSIZE7 1024 * 1024 * 400
#define MAXSIZE6 1024 * 1024 * 200
#define MAXSIZE5 1024 * 1024 * 200
#define MAXSIZE4 1024 * 1024 * 200
#define MAXSiZE3 1024 * 1024 * 200
const uint32_t MAX_SIZE_8_1=MAXSIZE8*(CS+0.2);//300M的内存
const uint32_t MAX_SIZE_7_1=MAXSIZE7*(CS+0.2);//300M的内存
const uint32_t MAX_SIZE_6_1=MAXSIZE6*(CS+0.2);//100M的内存
const uint32_t MAX_SIZE_5_1=MAXSIZE5*(CS+0.2);//50M的内存1024 * 1024 * 30
const uint32_t MAX_SIZE_4_1=MAXSIZE4*(CS+0.2);//40M的内存
const uint32_t MAX_SIZE_3_1=MAXSiZE3*(CS+0.2);//30M的内存
const uint32_t MAX_SIZE_8_2 = MAXSIZE8*(0.8-CS);//300M的内存
const uint32_t MAX_SIZE_7_2 = MAXSIZE7*(0.8-CS);//300M的内存
const uint32_t MAX_SIZE_6_2 = MAXSIZE6*(0.8-CS);//100M的内存
const uint32_t MAX_SIZE_5_2 = MAXSIZE5*(0.8-CS);//50M的内存
const uint32_t MAX_SIZE_4_2 = MAXSIZE4*(0.8-CS);//40M的内存
const uint32_t MAX_SIZE_3_2 = MAXSiZE3*(0.8-CS);//30M的内存
char **idsComma; //0...n to sorted id
char **idsLF; //0...n to sorted id
Node **G_O;
Node **G_I;
Node **G_O1;
Node **G_I1;
uint32_t *inDegrees;
uint32_t *outDegrees;
uint32_t *inDegrees_tmp;
uint32_t *outDegrees_tmp;
char buf_path[30];
int idx_1=0,idx_2=0;
vector<float> inputs;
vector<uint32_t> inputs_id;
unordered_map<uint32_t , uint32_t> idHash;
unordered_map<uint32_t , uint32_t> reidHash;
uint32_t nodecnt = 0;
uint32_t *HashTB,*HashTB1;
uint32_t *que;
int front=0,rear=0;
uint32_t *strsz;
pthread_mutex_t mutex1_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3_4 = PTHREAD_MUTEX_INITIALIZER;
uint32_t s1,e1;
uint32_t s2,e2;
/**线程1参数**/
float judge = 0.0;
char ans3[MAX_SIZE_3_1];
char ans4[MAX_SIZE_4_1];
char ans5[MAX_SIZE_5_1];
char ans6[MAX_SIZE_6_1];
char ans7[MAX_SIZE_7_1];
char ans8[MAX_SIZE_8_1];
char *ans3p;
char *ans4p;
char *ans5p;
char *ans6p;
char *ans7p;
char *ans8p;
uint32_t *distancej;
float *distanceje;
bool *visit;
int cnt1=0,cnt2=0,cnt3=0,cnt4=0,cnt5=0, cnt6=0;
uint32_t c_len1=0,c_len2=0,c_len3=0,c_len4=0,c_len5=0,c_len6=0;
Node *pos1, *pos2, *pos3, *pos4, *pos5, *pos6, *pos7, *pos8;
Node *end1, *end2, *end3, *end4, *end5, *end6, *end7, *end8;
uint32_t k_to,j_to, tt_to;
uint32_t n1, n2, n3, n4 ,n5;
Node p, q, r, s, t, u, v, w, nd;
float p_je,q_je,r_je,s_je,t_je, u_je, v_je, w_je;
uint32_t p_to,q_to,r_to,s_to,t_to, u_to, v_to, w_to;
/**线程2参数**/
float judge_1 = 0.0;
char ans3_1[MAX_SIZE_3_1];
char ans4_1[MAX_SIZE_4_1];
char ans5_1[MAX_SIZE_5_1];
char ans6_1[MAX_SIZE_6_1];
char ans7_1[MAX_SIZE_7_1];
char ans8_1[MAX_SIZE_8_1];
char *ans3p_1;
char *ans4p_1;
char *ans5p_1;
char *ans6p_1;
char *ans7p_1;
char *ans8p_1;
uint32_t *distancej_1;
float *distanceje_1;
bool *visit_1;
int cnt1_1=0,cnt2_1=0,cnt3_1=0,cnt4_1=0,cnt5_1=0,cnt6_1=0;
uint32_t c_len1_1=0,c_len2_1=0,c_len3_1=0,c_len4_1=0,c_len5_1=0,c_len6_1=0;
Node *pos1_1, *pos2_1, *pos3_1, *pos4_1, *pos5_1, *pos6_1, *pos7_1, *pos8_1;
Node *end1_1, *end2_1, *end3_1, *end4_1, *end5_1, *end6_1, *end7_1, *end8_1;
uint32_t k_to_1,j_to_1, tt_to_1;
uint32_t n1_1, n2_1, n3_1, n4_1 ,n5_1;
Node p_1, q_1, r_1, s_1, t_1, u_1, v_1, w_1;
float p_je_1,q_je_1,r_je_1,s_je_1,t_je_1, u_je_1, v_je_1, w_je_1;
uint32_t p_to_1,q_to_1,r_to_1,s_to_1,t_to_1, u_to_1,v_to_1, w_to_1;
/**线程3参数**/
float judge_2 = 0.0;
char ans3_2[MAX_SIZE_3_2];
char ans4_2[MAX_SIZE_4_2];
char ans5_2[MAX_SIZE_5_2];
char ans6_2[MAX_SIZE_6_2];
char ans7_2[MAX_SIZE_7_2];
char ans8_2[MAX_SIZE_8_2];
char *ans3p_2;
char *ans4p_2;
char *ans5p_2;
char *ans6p_2;
char *ans7p_2;
char *ans8p_2;
uint32_t *distancej_2;
float *distanceje_2;
bool *visit_2;
int cnt1_2=0,cnt2_2=0,cnt3_2=0,cnt4_2=0,cnt5_2=0, cnt6_2=0;
uint32_t c_len1_2=0,c_len2_2=0,c_len3_2=0,c_len4_2=0,c_len5_2=0,c_len6_2=0;
Node *pos1_2, *pos2_2, *pos3_2, *pos4_2, *pos5_2, *pos6_2, *pos7_2, *pos8_2;
Node *end1_2, *end2_2, *end3_2, *end4_2, *end5_2, *end6_2, *end7_2, *end8_2;
uint32_t k_to_2,j_to_2, tt_to_2;
uint32_t n1_2, n2_2, n3_2, n4_2 ,n5_2;
Node p_2, q_2, r_2, s_2, t_2, u_2, v_2, w_2;
float p_je_2,q_je_2,r_je_2,s_je_2,t_je_2, u_je_2, v_je_2, w_je_2;
uint32_t p_to_2,q_to_2,r_to_2,s_to_2,t_to_2, u_to_2, v_to_2, w_to_2;
/**线程4参数**/
float judge_3 = 0.0;
char ans3_3[MAX_SIZE_3_2];
char ans4_3[MAX_SIZE_4_2];
char ans5_3[MAX_SIZE_5_2];
char ans6_3[MAX_SIZE_6_2];
char ans7_3[MAX_SIZE_7_2];
char ans8_3[MAX_SIZE_8_2];
char *ans3p_3;
char *ans4p_3;
char *ans5p_3;
char *ans6p_3;
char *ans7p_3;
char *ans8p_3;
uint32_t *distancej_3;
float *distanceje_3;
bool *visit_3;
int cnt1_3=0,cnt2_3=0,cnt3_3=0,cnt4_3=0,cnt5_3=0, cnt6_3=0;
uint32_t c_len1_3=0,c_len2_3=0,c_len3_3=0,c_len4_3=0,c_len5_3=0, c_len6_3=0;
Node *pos1_3, *pos2_3, *pos3_3, *pos4_3, *pos5_3, *pos6_3, *pos7_3, *pos8_3;
Node *end1_3, *end2_3, *end3_3, *end4_3, *end5_3, *end6_3, *end7_3, *end8_3;
uint32_t k_to_3,j_to_3, tt_to_3;
uint32_t n1_3, n2_3, n3_3, n4_3 ,n5_3;
Node p_3, q_3, r_3, s_3, t_3, u_3, v_3, w_3;
float p_je_3,q_je_3,r_je_3,s_je_3,t_je_3, u_je_3, v_je_3, w_je_3;
uint32_t p_to_3,q_to_3,r_to_3,s_to_3,t_to_3, u_to_3, v_to_3, w_to_3;


inline void Input_Graph(const char * &testFile) {
#ifdef TEST_READ
    int tm = clock();
#endif
    size_t length;
    int fd = open(testFile, O_RDONLY);
    // obtain file size
    struct stat sb{};
    fstat(fd, &sb);
    length = sb.st_size;
    const char* addr = static_cast<const char*>(mmap(nullptr, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    auto e = addr + length;
    uint32_t t1 = 0;
    float t2 = 0.0;
    int fla = 1;
    int div = 10;
    inputs.reserve(MAX_E);
    inputs_id.reserve(MAX_E*2);
    while(addr!=e) {
        while(*addr!=','){
            t1 = t1 * 10 + *addr - '0';
            addr++;
        }
        inputs_id.push_back(t1);
        addr++;
        t1=0;
        while(*addr!=','){
            t1 = t1 * 10 + *addr - '0';
            addr++;
        }
        inputs_id.push_back(t1);
        addr++;
        t1=0;
        while(*addr!='\r'){
            if(*addr == '.')fla = 0;
            switch(fla){
                case 1: {
                    t1 = t1 * 10 + *addr - '0';
                    break;
                }
                case 0: {
                    t2 = t2 + *addr * (1.0/div);
                    div *= 10;
                    break;
                }
                default:
                    break;
            }
            addr++;
        }
        t2 += t1;
        inputs.push_back(t2);
        t1=0;
        t2 = 0.0;
        div = 10;
        fla = 1;
        addr += 2;
    }
    munmap((void *) addr, length);
    close(fd);
#ifdef TEST_READ
    cout<<"Read Time:"<<clock()-tm<<endl;
    cout<<"Records:"<<icnt<<endl;
#endif
}
inline void EnQueIn(uint32_t start_, uint32_t end_){
    for (int i = start_; i <= end_; i += 1) {
        if (0 == inDegrees[i]) {//入队
            que[rear++]=i;
        }
    }
}
inline void EnQueOut(uint32_t start_, uint32_t end_){
    for (int i = start_; i < end_; i += 1) {
        if (0 == outDegrees_tmp[i]) {//入队
            que[rear++]=i;
        }
    }
}
inline void parseInput(){
    auto tmp = inputs_id;
    uint32_t st,ed;
    uint32_t w;
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for (uint32_t &x : tmp) {
        idHash[x] = nodecnt;
        reidHash[nodecnt] = x;
        nodecnt++;
    }
    inDegrees = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(inDegrees,0,sizeof(uint32_t)*nodecnt);
    inDegrees_tmp = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(inDegrees_tmp,0,sizeof(uint32_t)*nodecnt);
    outDegrees = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(outDegrees,0,sizeof(uint32_t)*nodecnt);
    outDegrees_tmp = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(outDegrees_tmp,0,sizeof(uint32_t)*nodecnt);
    HashTB = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(HashTB,0,sizeof(uint32_t)*nodecnt);
    HashTB1 = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(HashTB1,0,sizeof(uint32_t)*nodecnt);
    que = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    G_O = (Node**)malloc(sizeof(Node*) * nodecnt);
    G_O1 = (Node**)malloc(sizeof(Node*) * nodecnt);
    G_I1 = (Node**)malloc(sizeof(Node*) * nodecnt);
    distancej = (uint32_t *)malloc(sizeof(uint32_t) * nodecnt);
    distanceje = (float *)malloc(sizeof(float) * nodecnt);
    distancej_1 = (uint32_t *)malloc(sizeof(uint32_t) * nodecnt);
    distanceje_1 = (float *)malloc(sizeof(float) * nodecnt);
    distancej_2 = (uint32_t *)malloc(sizeof(uint32_t) * nodecnt);
    distanceje_2 = (float *)malloc(sizeof(float) * nodecnt);
    distancej_3 = (uint32_t *)malloc(sizeof(uint32_t) * nodecnt);
    distanceje_3 = (float *)malloc(sizeof(float) * nodecnt);


#ifdef TEST
    printf("%d Nodes in Total\n", nodecnt);
#endif
    uint32_t *p_out;
    Node **g_o;
    int sz = inputs.size();
    uint32_t idx;
    for (int i = 0; i < sz; i += 1) {
        idx = 2*i;
        st = idHash[inputs_id[idx]];
        ed = idHash[inputs_id[idx + 1]];
        w = inputs[i];
        nd.to =ed;
        nd.je=w;
        p_out = &outDegrees[st];
        g_o = &G_O[st];
        if(!HashTB[st]){//没访问过
            HashTB[st] =1;
            *g_o=(Node*)malloc(OUTMAX*sizeof(Node));
        }else{//访问过
            switch ((*p_out+1)&(OUTMAX-1)) {
                case 0:{
                    *g_o = (Node*)realloc(*g_o,(*p_out+OUTMAX)*sizeof(Node));
                    break;
                }
            }
        }
        (*g_o)[*p_out]=nd;
        (*p_out)++;
        inDegrees[ed]++;
    }
    free(HashTB);
}
inline void topoSort(){
    Node tmp{};
    //入度拓扑
    EnQueIn(0, nodecnt);
    while(front!=rear){//正向拓扑排序
        int ut =que[front++];
        auto gu = G_O[ut];
        for(uint32_t i=0;i<outDegrees[ut];i+=1){
            tmp = gu[i];
            if(0==--inDegrees[tmp.to]){
                que[rear++]=tmp.to;
            }
        }
    }
    G_I =(Node**)malloc(sizeof(Node*) * nodecnt);
    //构建临时逆邻接表(入度大于0时构建)
    uint32_t i_size,o_to,*p_in;
    Node **g_i;
    for(uint32_t itr=0;itr<nodecnt;itr++){
        i_size = inDegrees[itr];
        if(i_size) {
            uint32_t &tempSize = outDegrees[itr];
            for(int j=0;j<tempSize;j++){
                auto &o = G_O[itr][j];
                o_to = o.to;
                tmp.set(itr,o.je);
                g_i = &G_I[o_to];
                p_in = &inDegrees_tmp[o_to];
                if(!HashTB1[o_to]){//没访问过
                    HashTB1[o_to] =1;
                    *g_i=(Node*)malloc(INMAX*sizeof(Node));
                }else{
                    switch ((*p_in+1)&(INMAX-1)) {
                        case 0:{
                            *g_i = (Node*)realloc(*g_i,(*p_in+INMAX)*sizeof(Node));
                            break;
                        }
                    }
                }
                (*g_i)[*p_in] = tmp;
                (*p_in)++;
                outDegrees_tmp[itr]++;
            }
        }
        outDegrees[itr]=0;
        inDegrees[itr]=0;
    }
    free(HashTB1);
    free(G_O);
    //出度拓扑
    front = 0;
    rear = 0;
    EnQueOut(0,nodecnt);
    while(front!=rear){
        uint32_t o = que[front++];
        i_size = inDegrees_tmp[o];
        for(int itr=0; itr<i_size; itr++){
            auto i = G_I[o][itr];
            int v= i.to;
            if(0 == --outDegrees_tmp[v]){
                que[rear++] = v;
            }
        }
    }
    idsComma = (char**)malloc(sizeof(char*)*nodecnt);
    idsLF = (char**)malloc(sizeof(char*)*nodecnt);
    char **Comma,**LF;
    uint32_t *outP,*inP;
    Node **g_o1,**g_i1;
    HashTB = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(HashTB,0,sizeof(uint32_t)*nodecnt);
    HashTB1 = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(HashTB1,0,sizeof(uint32_t)*nodecnt);
    strsz = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    //构造新的邻接表和逆邻接表(入度>0且出度>0)
    for(uint32_t itr=0;itr<nodecnt;itr++){
        if(outDegrees_tmp[itr]){//入度小于等于0时outDegree_tmp自动为0
            uint32_t tid = reidHash[itr];
            idx_1=sprintf(buf_path, "%d", tid);
            idx_2=idx_1;
            buf_path[idx_1++]=',';
            buf_path[idx_1]='\0';
            Comma = &idsComma[itr];
            strsz[itr] = idx_1;
            *Comma = (char*)malloc(40*sizeof(char));
            strcpy(*Comma,buf_path);
            buf_path[idx_2++]='\n';
            buf_path[idx_2]='\0';
            LF = &idsLF[itr];
            *LF=(char*)malloc(40*sizeof(char));
            strcpy(*LF,buf_path);
            uint32_t &inSize =  inDegrees_tmp[itr];
            for(int j=0; j<inSize; j++) {
                auto &x = G_I[itr][j];
                int v = x.to;
                outP = &outDegrees[v];
                inP = &inDegrees[itr];
                g_o1 = &G_O1[v];
                g_i1 = &G_I1[itr];
                if(!HashTB[v]){//没访问过,出度默认开100
                    HashTB[v] =1;
                    *g_o1=(Node*)malloc(OUTMAX*sizeof(Node));
                }else{
                    switch ((*outP+1)&(OUTMAX-1)) {
                        case 0:{
                            *g_o1 = (Node*)realloc(*g_o1,(*outP+OUTMAX)*sizeof(Node));
                            break;
                        }
                    }
                }
                if(!HashTB1[itr]){//没访问过
                    HashTB1[itr] =1;
                    *g_i1=(Node*)malloc(INMAX*sizeof(Node));
                }else{
                    switch ((*inP+1)&(INMAX-1)) {
                        case 0:{
                            *g_i1 = (Node*)realloc(*g_i1,(*inP+INMAX)*sizeof(Node));
                            break;
                        }
                    }
                }
                tmp.set(itr,x.je);
                (*g_o1)[*outP] = tmp;
                (*g_i1)[*inP] = x;
                (*outP)++;
                (*inP)++;
            }
        }
    }
    free(HashTB);
    free(HashTB1);
    free(G_I);
    free(inDegrees_tmp);
    free(outDegrees_tmp);
}
inline void dfs(uint32_t & i) {
    auto gi = G_O1[i];
    end1 = gi + outDegrees[i];
    for (pos1 = gi; pos1 < end1; ++pos1) {//i->p
        p = *pos1;
        p_to = p.to;
        if(p_to <= i || visit[p_to]) continue;
        p_je=p.je;
        visit[p_to] = true;
        n1 = outDegrees[p_to];
        if(n1==0) continue;
        auto gp = G_O1[p_to];
        end2 = gp + n1;
        for (pos2=gp; pos2 < end2; ++pos2) {
            q = *pos2;
            q_to = q.to;
            if (q_to <= i || visit[q_to])continue;
            q_je = q.je;
#ifdef JEJUDGE
            judge = 1.0 * q_je / p_je;
            if(judge<MINJE || judge>MAXJE) continue;
#endif
            visit[q_to] = true;
            n2 = outDegrees[q_to];
            if (n2 == 0) continue;
            auto gq = G_O1[q_to];
            end3 = gq + n2;
            for (pos3 = gq; pos3 < end3; ++pos3) {//i-p-q
                r = *pos3;
                r_to = r.to;
                if (r_to < i || visit[r_to]) continue;
                r_je = r.je;
#ifdef JEJUDGE
                judge = 1.0 * r_je/q_je;
                if(judge<MINJE || judge>MAXJE) continue;
#endif
                if(r_to==i){
                    judge = 1.0 * p_je / r_je;
                    if(judge<MINJE || judge>MAXJE) continue;
                    auto res =idsComma[i];
                    memcpy(ans3p, res, strsz[i]);
                    ans3p+=strsz[i];
                    res = idsComma[p_to];
                    memcpy(ans3p, res, strsz[p_to]);
                    ans3p+=strsz[p_to];
                    res=idsLF[q_to];
                    memcpy(ans3p, res, strsz[q_to]);
                    ans3p+=strsz[q_to];
                    cnt1++;
                    continue;
                }
                visit[r_to] = true;
                n3 = outDegrees[r_to];
                if (n3 == 0) continue;
                auto gr = G_O1[r_to];
                end4 = gr + n3;
                for (pos4 = gr; pos4 < end4; pos4++) {//begin remove node
                    s = *pos4;//i-p-q-r-s
                    s_to = s.to;
                    if (s_to < i || visit[s_to]) continue;
                    s_je = s.je;
#ifdef JEJUDGE
                    judge = 1.0 * s_je/r_je;
                    if(judge<MINJE || judge>MAXJE) continue;
#endif
                    if(s_to == i){
                        judge = 1.0 * p_je / s_je;
                        if(judge<MINJE || judge>MAXJE) continue;
                        auto res =idsComma[i];
                        memcpy(ans4p, res, strsz[i]);
                        ans4p+=strsz[i];
                        res = idsComma[p_to];
                        memcpy(ans4p, res, strsz[p_to]);
                        ans4p+=strsz[p_to];
                        res=idsComma[q_to];
                        memcpy(ans4p, res, strsz[q_to]);
                        ans4p+=strsz[q_to];
                        res=idsLF[r_to];
                        memcpy(ans4p, res, strsz[r_to]);
                        ans4p+=strsz[r_to];
                        cnt2++;
                        continue;
                    }
                    visit[s_to]=true;
                    n4 = outDegrees[s_to];
                    if(n4==0)continue;
                    auto gs = G_O1[s_to];
                    end5 = gs + n4;
                    for(pos5 = gs; pos5<end5; pos5++){
                        t = *pos5;
                        t_to = t.to;
                        if(t_to <i ||visit[t_to]||distancej[t_to]>3) continue;
                        t_je = t.je;
                        //(s)-t-u-i不需要再判断内部节点
                        judge = 1.0 * t_je / s_je;
                        if(judge<MINJE || judge>MAXJE) continue;
                        if(t_to == i){
                            judge = 1.0 * p_je / t_je;
                            if(judge<MINJE || judge>MAXJE) continue;
                            auto res =idsComma[i];
                            memcpy(ans5p, res, strsz[i]);
                            ans5p+=strsz[i];
                            res = idsComma[p_to];
                            memcpy(ans5p, res, strsz[p_to]);
                            ans5p+=strsz[p_to];
                            res=idsComma[q_to];
                            memcpy(ans5p, res, strsz[q_to]);
                            ans5p+=strsz[q_to];
                            res=idsComma[r_to];
                            memcpy(ans5p, res, strsz[r_to]);
                            ans5p+=strsz[r_to];
                            res=idsLF[s_to];
                            memcpy(ans5p, res, strsz[s_to]);
                            ans5p+=strsz[s_to];
                            cnt3++;
                            continue;
                        }
                        visit[t_to] = true;
                        n5 = outDegrees[t_to];
                        if(n5==0)continue;
                        auto gt = G_O1[t_to];
                        end6 = gt + n5;
                        for(pos6 = gt; pos6<end6; pos6++){
                            u = *pos6;
                            u_to = u.to;
                            if(u_to <i ||visit[u_to]||distancej[u_to]>2) continue;
                            u_je = u.je;
                            judge = 1.0 * u_je / t_je;
                            if(judge<MINJE || judge>MAXJE) continue;
                            if(u_to == i){
                                judge = 1.0 * p_je / u_je;
                                if(judge<MINJE || judge>MAXJE) continue;
                                auto res =idsComma[i];
                                memcpy(ans6p, res, strsz[i]);
                                ans6p+=strsz[i];
                                res = idsComma[p_to];
                                memcpy(ans6p, res, strsz[p_to]);
                                ans6p+=strsz[p_to];
                                res=idsComma[q_to];
                                memcpy(ans6p, res, strsz[q_to]);
                                ans6p+=strsz[q_to];
                                res=idsComma[r_to];
                                memcpy(ans6p, res, strsz[r_to]);
                                ans6p+=strsz[r_to];
                                res=idsComma[s_to];
                                memcpy(ans6p, res, strsz[s_to]);
                                ans6p+=strsz[s_to];
                                res=idsLF[t_to];
                                memcpy(ans6p, res, strsz[t_to]);
                                ans6p+=strsz[t_to];
                                cnt4++;
                                continue;
                            }
                            visit[u_to] = true;
                            auto gu = G_O1[u_to];
                            end7 = gu+outDegrees[u_to];

                            for(pos7=gu;pos7<end7;pos7++){
                                v = *pos7;
                                v_to = v.to;
                                if(v_to <i ||visit[v_to]||distancej[v_to]>1) continue;
                                v_je = v.je;
                                judge = 1.0 * v_je / u_je;
                                if(judge<MINJE || judge>MAXJE) continue;
                                if(v_to == i){
                                    judge = 1.0 * p_je / v_je;
                                    if(judge<MINJE || judge>MAXJE) continue;
                                    auto res =idsComma[i];
                                    memcpy(ans7p, res, strsz[i]);
                                    ans7p+=strsz[i];
                                    res = idsComma[p_to];
                                    memcpy(ans7p, res, strsz[p_to]);
                                    ans7p+=strsz[p_to];
                                    res=idsComma[q_to];
                                    memcpy(ans7p, res, strsz[q_to]);
                                    ans7p+=strsz[q_to];
                                    res=idsComma[r_to];
                                    memcpy(ans7p, res, strsz[r_to]);
                                    ans7p+=strsz[r_to];
                                    res=idsComma[s_to];
                                    memcpy(ans7p, res, strsz[s_to]);
                                    ans7p+=strsz[s_to];
                                    res=idsComma[t_to];
                                    memcpy(ans7p, res, strsz[t_to]);
                                    ans7p+=strsz[t_to];
                                    res=idsLF[u_to];
                                    memcpy(ans7p, res, strsz[u_to]);
                                    ans7p+=strsz[u_to];
                                    cnt5++;
                                    continue;
                                }
                                auto gv = G_O1[v_to];
                                end8 = gv+outDegrees[v_to];

                                for(pos8=gv;pos8<end8;pos8++){
                                    w = *pos8;
                                    if (w.to != i) continue;
                                    judge = 1.0*w.je/v_je;
                                    if(judge<MINJE || judge>MAXJE) continue;
                                    judge =1.0*p_je/w.je;
                                    if(judge<MINJE || judge>MAXJE) continue;
                                    auto res = idsComma[i];
                                    memcpy(ans8p, res, strsz[i]);
                                    ans8p += strsz[i];
                                    res = idsComma[p_to];
                                    memcpy(ans8p, res, strsz[p_to]);
                                    ans8p += strsz[p_to];
                                    res = idsComma[q_to];
                                    memcpy(ans8p, res, strsz[q_to]);
                                    ans8p += strsz[q_to];
                                    res = idsComma[r_to];
                                    memcpy(ans8p, res, strsz[r_to]);
                                    ans8p += strsz[r_to];
                                    res = idsComma[s_to];
                                    memcpy(ans8p, res, strsz[s_to]);
                                    ans8p += strsz[s_to];
                                    res = idsComma[t_to];
                                    memcpy(ans8p, res, strsz[t_to]);
                                    ans8p += strsz[t_to];
                                    res = idsComma[u_to];
                                    memcpy(ans8p, res, strsz[u_to]);
                                    ans8p += strsz[u_to];
                                    res = idsLF[v_to];
                                    memcpy(ans8p, res, strsz[v_to]);
                                    ans8p += strsz[v_to];
                                    cnt6++;
                                }
                            }
                            visit[u_to] = true;
                        }
                        visit[t_to] = false;
                    }
                    visit[s_to]=false;
                }
                visit[r_to] = false;
            }
            visit[q_to] = false;
        }
        visit[p_to] = false;
    }
}
inline void dfs_1(uint32_t & i) {
    auto gi = G_O1[i];
    end1_1 = gi + outDegrees[i];
    for (pos1_1 = end1_1-1; pos1_1 >= gi; --pos1_1) {//i->p
        p_1 = *pos1_1;
        p_to_1 = p_1.to;
        if(p_to_1 <= i || visit_1[p_to_1]) continue;
        p_je_1=p_1.je;
        visit_1[p_to_1] = true;
        n1_1 = outDegrees[p_to_1];
        if(n1_1==0) continue;
        auto gp = G_O1[p_to_1];
        end2_1 = gp + n1_1;
        for (pos2_1=end2_1-1; pos2_1 >= gp; --pos2_1) {
            q_1 = *pos2_1;
            q_to_1 = q_1.to;
            if (q_to_1 <= i || visit_1[q_to_1])continue;
            q_je_1 = q_1.je;
#ifdef JEJUDGE
            judge_1 = 1.0 * q_je_1 / p_je_1;
            if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
            visit_1[q_to_1] = true;
            n2_1 = outDegrees[q_to_1];
            if (n2_1 == 0) continue;
            auto gq = G_O1[q_to_1];
            end3_1 = gq + n2_1;
            for (pos3_1 = end3_1-1; pos3_1 >= gq; --pos3_1) {//i-p-q
                r_1 = *pos3_1;
                r_to_1 = r_1.to;
                if (r_to_1 < i || visit_1[r_to_1]) continue;
                r_je_1 = r_1.je;
#ifdef JEJUDGE
                judge_1 = 1.0 * r_je_1/q_je_1;
                if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                if(r_to_1==i){
                    judge_1 = 1.0 * p_je_1 / r_je_1;
                    if(judge_1<MINJE || judge_1>MAXJE) continue;
                    auto res=idsLF[q_to_1];
                    ans3p_1 -= strsz[q_to_1];
                    memcpy(ans3p_1, res, strsz[q_to_1]);
                    res = idsComma[p_to_1];
                    ans3p_1 -= strsz[p_to_1];
                    memcpy(ans3p_1, res, strsz[p_to_1]);
                    res =idsComma[i];
                    ans3p_1 -= strsz[i];
                    memcpy(ans3p_1, res, strsz[i]);
                    cnt1_1++;
                    continue;
                }
                visit_1[r_to_1] = true;
                n3_1 = outDegrees[r_to_1];
                if (n3_1 == 0) continue;
                auto gr = G_O1[r_to_1];
                end4_1 = gr + n3_1;
                for (pos4_1 = end4_1-1; pos4_1 >= gr; --pos4_1) {//begin remove node
                    s_1 = *pos4_1;//i-p-q-r-s
                    s_to_1 = s_1.to;
                    if (s_to_1 < i || visit_1[s_to_1]) continue;
                    s_je_1 = s_1.je;
#ifdef JEJUDGE
                    judge_1 = 1.0 * s_je_1/r_je_1;
                    if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                    if(s_to_1 == i){
                        judge_1 = 1.0 * p_je_1 / s_je_1;
                        if(judge_1<MINJE || judge_1>MAXJE) continue;
                        auto res = idsLF[r_to_1];
                        ans4p_1 -= strsz[r_to_1];
                        memcpy(ans4p_1, res, strsz[r_to_1]);
                        res=idsComma[q_to_1];
                        ans4p_1 -= strsz[q_to_1];
                        memcpy(ans4p_1, res, strsz[q_to_1]);
                        res = idsComma[p_to_1];
                        ans4p_1 -= strsz[p_to_1];
                        memcpy(ans4p_1, res, strsz[p_to_1]);
                        res =idsComma[i];
                        ans4p_1 -= strsz[i];
                        memcpy(ans4p_1, res, strsz[i]);
                        cnt2_1++;
                        continue;
                    }
                    visit_1[s_to_1]=true;
                    n4_1 = outDegrees[s_to_1];
                    if(n4_1==0)continue;
                    auto gs = G_O1[s_to_1];
                    end5_1 = gs + n4_1;
                    for(pos5_1=end5_1-1; pos5_1>=gs; --pos5_1){
                        t_1 = *pos5_1;
                        t_to_1 = t_1.to;
                        if(t_to_1 <i ||visit_1[t_to_1]||distancej_1[t_to_1]>3) continue;
                        t_je_1 = t_1.je;
                        //(s)-t-u-i不需要再判断内部节点
                        judge_1 = 1.0 * t_je_1 / s_je_1;
                        if(judge_1<MINJE || judge_1>MAXJE) continue;
                        if(t_to_1 == i){
                            judge_1 = 1.0 * p_je_1 / t_je_1;
                            if(judge_1<MINJE || judge_1>MAXJE) continue;
                            auto res=idsLF[s_to_1];
                            ans5p_1 -= strsz[s_to_1];
                            memcpy(ans5p_1, res, strsz[s_to_1]);
                            res=idsComma[r_to_1];
                            ans5p_1 -= strsz[r_to_1];
                            memcpy(ans5p_1, res, strsz[r_to_1]);
                            res=idsComma[q_to_1];
                            ans5p_1 -= strsz[q_to_1];
                            memcpy(ans5p_1, res, strsz[q_to_1]);
                            res = idsComma[p_to_1];
                            ans5p_1 -= strsz[p_to_1];
                            memcpy(ans5p_1, res, strsz[p_to_1]);
                            res =idsComma[i];
                            ans5p_1 -= strsz[i];
                            memcpy(ans5p_1, res, strsz[i]);
                            cnt3_1++;
                            continue;
                        }
                        visit_1[t_to_1] = true;
                        n5_1 = outDegrees[t_to_1];
                        if(n5_1==0)continue;
                        auto gt = G_O1[t_to_1];
                        end6_1 = gt + n5_1;
                        for(pos6_1 = end6_1-1; pos6_1>=gt; --pos6_1){
                            u_1 = *pos6_1;
                            u_to_1 = u_1.to;
                            if(u_to_1 <i ||visit_1[u_to_1]||distancej_1[u_to_1]>2) continue;
                            u_je_1 = u_1.je;
                            judge_1 = 1.0 * u_je_1 / t_je_1;
                            if(judge_1<MINJE || judge_1>MAXJE) continue;
                            if(u_to_1 == i){
                                judge_1 = 1.0 * p_je_1 / u_je_1;
                                if(judge_1<MINJE || judge_1>MAXJE) continue;
                                auto res=idsLF[t_to_1];
                                ans6p_1 -= strsz[t_to_1];
                                memcpy(ans6p_1, res, strsz[t_to_1]);
                                res=idsComma[s_to_1];
                                ans6p_1 -= strsz[s_to_1];
                                memcpy(ans6p_1, res, strsz[s_to_1]);
                                res=idsComma[r_to_1];
                                ans6p_1 -= strsz[r_to_1];
                                memcpy(ans6p_1, res, strsz[r_to_1]);
                                res=idsComma[q_to_1];
                                ans6p_1 -= strsz[q_to_1];
                                memcpy(ans6p_1, res, strsz[q_to_1]);
                                res = idsComma[p_to_1];
                                ans6p_1 -= strsz[p_to_1];
                                memcpy(ans6p_1, res, strsz[p_to_1]);
                                res =idsComma[i];
                                ans6p_1 -= strsz[i];
                                memcpy(ans6p_1, res, strsz[i]);
                                cnt4_1++;
                                continue;
                            }
                            visit_1[u_to_1] = true;
                            auto gu = G_O1[u_to_1];
                            end7_1 = gu+outDegrees[u_to_1];

                            for(pos7_1=end7_1-1; pos7_1>=gu;--pos7_1){
                                v_1 = *pos7_1;
                                v_to_1 = v_1.to;
                                v_je_1 = v_1.je;
                                if (v_to_1 <i ||visit_1[v_to_1]||distancej_1[v_to_1]>1) continue;
                                judge_1 = 1.0*v_je_1/u_je_1;
                                if(judge_1<MINJE || judge_1>MAXJE) continue;
                                if(v_to_1==i) {
                                    judge_1 = 1.0 * p_je_1 / v_je_1;
                                    if (judge_1 < MINJE || judge_1 > MAXJE) continue;
                                    auto res = idsLF[u_to_1];
                                    ans7p_1 -= strsz[u_to_1];
                                    memcpy(ans7p_1, res, strsz[u_to_1]);
                                    res = idsComma[t_to_1];
                                    ans7p_1 -= strsz[t_to_1];
                                    memcpy(ans7p_1, res, strsz[t_to_1]);
                                    res = idsComma[s_to_1];
                                    ans7p_1 -= strsz[s_to_1];
                                    memcpy(ans7p_1, res, strsz[s_to_1]);
                                    res = idsComma[r_to_1];
                                    ans7p_1 -= strsz[r_to_1];
                                    memcpy(ans7p_1, res, strsz[r_to_1]);
                                    res = idsComma[q_to_1];
                                    ans7p_1 -= strsz[q_to_1];
                                    memcpy(ans7p_1, res, strsz[q_to_1]);
                                    res = idsComma[p_to_1];
                                    ans7p_1 -= strsz[p_to_1];
                                    memcpy(ans7p_1, res, strsz[p_to_1]);
                                    res = idsComma[i];
                                    ans7p_1 -= strsz[i];
                                    memcpy(ans7p_1, res, strsz[i]);
                                    cnt5_1++;
                                }
                                auto gv = G_O1[v_to_1];
                                end8_1 = gv+outDegrees[v_to_1];

                                for(pos8_1=end8_1-1;pos8_1>=gv;--pos8_1){
                                    w_1 = *pos8_1;
                                    if (w_1.to != i) continue;
                                    judge_1 = 1.0*w_1.je/v_je_1;
                                    if(judge_1<MINJE || judge_1>MAXJE) continue;
                                    judge_1 =1.0*p_je_1/w_1.je;
                                    if(judge_1<MINJE || judge_1>MAXJE) continue;
                                    auto res = idsLF[v_to_1];
                                    ans8p_1 -= strsz[v_to_1];
                                    memcpy(ans8p_1, res, strsz[v_to_1]);
                                    res = idsComma[u_to_1];
                                    ans8p_1 -= strsz[u_to_1];
                                    memcpy(ans8p_1, res, strsz[u_to_1]);
                                    res = idsComma[t_to_1];
                                    ans8p_1 -= strsz[t_to_1];
                                    memcpy(ans8p_1, res, strsz[t_to_1]);
                                    res = idsComma[s_to_1];
                                    ans8p_1 -= strsz[s_to_1];
                                    memcpy(ans8p_1, res, strsz[s_to_1]);
                                    res = idsComma[r_to_1];
                                    ans8p_1 -= strsz[r_to_1];
                                    memcpy(ans8p_1, res, strsz[r_to_1]);
                                    res = idsComma[q_to_1];
                                    ans8p_1 -= strsz[q_to_1];
                                    memcpy(ans8p_1, res, strsz[q_to_1]);
                                    res = idsComma[p_to_1];
                                    ans8p_1 -= strsz[p_to_1];
                                    memcpy(ans8p_1, res, strsz[p_to_1]);
                                    res = idsComma[i];
                                    ans8p_1 -= strsz[i];
                                    memcpy(ans8p_1, res, strsz[i]);
                                    cnt6_1++;
                                }
                            }
                            visit_1[u_to_1] = false;
                        }
                        visit_1[t_to_1] = false;
                    }
                    visit_1[s_to_1]=false;
                }
                visit_1[r_to_1] = false;
            }
            visit_1[q_to_1] = false;
        }
        visit_1[p_to_1] = false;
    }
}
inline void dfs_2(uint32_t & i) {
    auto gi = G_O1[i];
    end1_2 = gi + outDegrees[i];
    for (pos1_2 = gi; pos1_2 < end1_2; ++pos1_2) {//i->p
        p_2 = *pos1_2;
        p_to_2 = p_2.to;
        if(p_to_2 <= i || visit_2[p_to_2]) continue;
        p_je_2=p_2.je;
        visit_2[p_to_2] = true;
        n1_2 = outDegrees[p_to_2];
        if(n1_2==0) continue;
        auto gp = G_O1[p_to_2];
        end2_2 = gp + n1_2;
        for (pos2_2=gp; pos2_2 < end2_2; ++pos2_2) {
            q_2 = *pos2_2;
            q_to_2 = q_2.to;
            if (q_to_2 <= i || visit_2[q_to_2])continue;
            q_je_2 = q_2.je;
#ifdef JEJUDGE
            judge_2 = 1.0 * q_je_2 / p_je_2;
            if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
            visit_2[q_to_2] = true;
            n2_2 = outDegrees[q_to_2];
            if (n2_2 == 0) continue;
            auto gq = G_O1[q_to_2];
            end3_2 = gq + n2_2;
            for (pos3_2 = gq; pos3_2 < end3_2; ++pos3_2) {//i-p-q
                r_2 = *pos3_2;
                r_to_2 = r_2.to;
                if (r_to_2 < i || visit_2[r_to_2]) continue;
                r_je_2 = r_2.je;
#ifdef JEJUDGE
                judge_2 = 1.0 * r_je_2/q_je_2;
                if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
                if(r_to_2==i){
                    judge_2 = 1.0 * p_je_2 / r_je_2;
                    if(judge_2<MINJE || judge_2>MAXJE) continue;
                    auto res =idsComma[i];
                    memcpy(ans3p_2, res, strsz[i]);
                    ans3p_2+=strsz[i];
                    res = idsComma[p_to_2];
                    memcpy(ans3p_2, res, strsz[p_to_2]);
                    ans3p_2+=strsz[p_to_2];
                    res=idsLF[q_to_2];
                    memcpy(ans3p_2, res, strsz[q_to_2]);
                    ans3p_2+=strsz[q_to_2];
                    cnt1_2++;
                    continue;
                }
                visit_2[r_to_2] = true;
                n3_2 = outDegrees[r_to_2];
                if (n3_2 == 0) continue;
                auto gr = G_O1[r_to_2];
                end4_2 = gr + n3_2;
                for (pos4_2 = gr; pos4_2 < end4_2; pos4_2++) {//begin remove node
                    s_2 = *pos4_2;//i-p-q-r-s
                    s_to_2 = s_2.to;
                    if (s_to_2 < i || visit_2[s_to_2]) continue;
                    s_je_2 = s_2.je;
#ifdef JEJUDGE
                    judge_2 = 1.0 * s_je_2/r_je_2;
                    if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
                    if(s_to_2 == i){
                        judge_2 = 1.0 * p_je_2 / s_je_2;
                        if(judge_2<MINJE || judge_2>MAXJE) continue;
                        auto res =idsComma[i];
                        memcpy(ans4p_2, res, strsz[i]);
                        ans4p_2+=strsz[i];
                        res = idsComma[p_to_2];
                        memcpy(ans4p_2, res, strsz[p_to_2]);
                        ans4p_2+=strsz[p_to_2];
                        res=idsComma[q_to_2];
                        memcpy(ans4p_2, res, strsz[q_to_2]);
                        ans4p_2+=strsz[q_to_2];
                        res=idsLF[r_to_2];
                        memcpy(ans4p_2, res, strsz[r_to_2]);
                        ans4p_2+=strsz[r_to_2];
                        cnt2_2++;
                        continue;
                    }
                    visit_2[s_to_2]=true;
                    n4_2 = outDegrees[s_to_2];
                    if(n4_2==0)continue;
                    auto gs = G_O1[s_to_2];
                    end5_2 = gs + n4_2;
                    for(pos5_2 = gs; pos5_2<end5_2; pos5_2++){
                        t_2 = *pos5_2;
                        t_to_2 = t_2.to;
                        if(t_to_2 <i ||visit_2[t_to_2]||distancej_2[t_to_2]>3) continue;
                        t_je_2 = t_2.je;
                        //(s)-t-u-i不需要再判断内部节点
                        judge_2 = 1.0 * t_je_2 / s_je_2;
                        if(judge_2<MINJE || judge_2>MAXJE) continue;
                        if(t_to_2 == i){
                            judge_2 = 1.0 * p_je_2 / t_je_2;
                            if(judge_2<MINJE || judge_2>MAXJE) continue;
                            auto res =idsComma[i];
                            memcpy(ans5p_2, res, strsz[i]);
                            ans5p_2+=strsz[i];
                            res = idsComma[p_to_2];
                            memcpy(ans5p_2, res, strsz[p_to_2]);
                            ans5p_2+=strsz[p_to_2];
                            res=idsComma[q_to_2];
                            memcpy(ans5p_2, res, strsz[q_to_2]);
                            ans5p_2+=strsz[q_to_2];
                            res=idsComma[r_to_2];
                            memcpy(ans5p_2, res, strsz[r_to_2]);
                            ans5p_2+=strsz[r_to_2];
                            res=idsLF[s_to_2];
                            memcpy(ans5p_2, res, strsz[s_to_2]);
                            ans5p_2+=strsz[s_to_2];
                            cnt3_2++;
                            continue;
                        }
                        visit_2[t_to_2] = true;
                        n5_2 = outDegrees[t_to_2];
                        if(n5_2==0)continue;
                        auto gt = G_O1[t_to_2];
                        end6_2 = gt + n5_2;
                        for(pos6_2 = gt; pos6_2<end6_2; pos6_2++){
                            u_2 = *pos6_2;
                            u_to_2 = u_2.to;
                            if(u_to_2 <i ||visit_2[u_to_2]||distancej_2[u_to_2]>2) continue;
                            u_je_2 = u_2.je;
                            judge_2 = 1.0 * u_je_2 / t_je_2;
                            if(judge_2<MINJE || judge_2>MAXJE) continue;
                            if(u_to_2 == i){
                                judge_2 = 1.0 * p_je_2 / u_je_2;
                                if(judge_2<MINJE || judge_2>MAXJE) continue;
                                auto res =idsComma[i];
                                memcpy(ans6p_2, res, strsz[i]);
                                ans6p_2+=strsz[i];
                                res = idsComma[p_to_2];
                                memcpy(ans6p_2, res, strsz[p_to_2]);
                                ans6p_2+=strsz[p_to_2];
                                res=idsComma[q_to_2];
                                memcpy(ans6p_2, res, strsz[q_to_2]);
                                ans6p_2+=strsz[q_to_2];
                                res=idsComma[r_to_2];
                                memcpy(ans6p_2, res, strsz[r_to_2]);
                                ans6p_2+=strsz[r_to_2];
                                res=idsComma[s_to_2];
                                memcpy(ans6p_2, res, strsz[s_to_2]);
                                ans6p_2+=strsz[s_to_2];
                                res=idsLF[t_to_2];
                                memcpy(ans6p_2, res, strsz[t_to_2]);
                                ans6p_2+=strsz[t_to_2];
                                cnt4_2++;
                                continue;
                            }
                            visit_2[u_to_2] = true;
                            auto gu = G_O1[u_to_2];
                            end7_2 = gu+outDegrees[u_to_2];

                            for(pos7_2=gu;pos7_2<end7_2;pos7_2++){
                                v_2 = *pos7_2;
                                v_to_2 = v_2.to;
                                if(v_to_2 <i ||visit_2[v_to_2]||distancej_2[v_to_2]>1) continue;
                                v_je_2 = v_2.je;
                                judge_2 = 1.0 * v_je_2 / u_je_2;
                                if(judge_2<MINJE || judge_2>MAXJE) continue;
                                if(v_to_2 == i){
                                    judge_2 = 1.0 * p_je_2 / v_je_2;
                                    if(judge_2<MINJE || judge_2>MAXJE) continue;
                                    auto res =idsComma[i];
                                    memcpy(ans7p_2, res, strsz[i]);
                                    ans7p_2+=strsz[i];
                                    res = idsComma[p_to_2];
                                    memcpy(ans7p_2, res, strsz[p_to_2]);
                                    ans7p_2+=strsz[p_to_2];
                                    res=idsComma[q_to_2];
                                    memcpy(ans7p_2, res, strsz[q_to_2]);
                                    ans7p_2+=strsz[q_to_2];
                                    res=idsComma[r_to_2];
                                    memcpy(ans7p_2, res, strsz[r_to_2]);
                                    ans7p_2+=strsz[r_to_2];
                                    res=idsComma[s_to_2];
                                    memcpy(ans7p_2, res, strsz[s_to_2]);
                                    ans7p_2+=strsz[s_to_2];
                                    res=idsComma[t_to_2];
                                    memcpy(ans7p_2, res, strsz[t_to_2]);
                                    ans7p_2+=strsz[t_to_2];
                                    res=idsLF[u_to_2];
                                    memcpy(ans7p_2, res, strsz[u_to_2]);
                                    ans7p_2+=strsz[u_to_2];
                                    cnt5_2++;
                                    continue;
                                }
                                auto gv = G_O1[v_to_2];
                                end8_2 = gv+outDegrees[v_to_2];

                                for(pos8_2=gv;pos8_2<end8_2;pos8_2++){
                                    w_2 = *pos8_2;
                                    if (w_2.to != i) continue;
                                    judge_2 = 1.0*w_2.je/v_je_2;
                                    if(judge_2<MINJE || judge_2>MAXJE) continue;
                                    judge_2 =1.0*p_je_2/w_2.je;
                                    if(judge_2<MINJE || judge_2>MAXJE) continue;
                                    auto res = idsComma[i];
                                    memcpy(ans8p_2, res, strsz[i]);
                                    ans8p_2 += strsz[i];
                                    res = idsComma[p_to_2];
                                    memcpy(ans8p_2, res, strsz[p_to_2]);
                                    ans8p_2 += strsz[p_to_2];
                                    res = idsComma[q_to_2];
                                    memcpy(ans8p_2, res, strsz[q_to_2]);
                                    ans8p_2 += strsz[q_to_2];
                                    res = idsComma[r_to_2];
                                    memcpy(ans8p_2, res, strsz[r_to_2]);
                                    ans8p_2 += strsz[r_to_2];
                                    res = idsComma[s_to_2];
                                    memcpy(ans8p_2, res, strsz[s_to_2]);
                                    ans8p_2 += strsz[s_to_2];
                                    res = idsComma[t_to_2];
                                    memcpy(ans8p_2, res, strsz[t_to_2]);
                                    ans8p_2 += strsz[t_to_2];
                                    res = idsComma[u_to_2];
                                    memcpy(ans8p_2, res, strsz[u_to_2]);
                                    ans8p_2 += strsz[u_to_2];
                                    res = idsLF[v_to_2];
                                    memcpy(ans8p_2, res, strsz[v_to_2]);
                                    ans8p_2 += strsz[v_to_2];
                                    cnt6_2++;
                                }
                            }
                            visit_2[u_to_2] = true;
                        }
                        visit_2[t_to_2] = false;
                    }
                    visit_2[s_to_2]=false;
                }
                visit_2[r_to_2] = false;
            }
            visit_2[q_to_2] = false;
        }
        visit_2[p_to_2] = false;
    }
}
inline void dfs_3(uint32_t & i) {
    auto gi = G_O1[i];
    end1_3 = gi + outDegrees[i];
    for (pos1_3 = end1_3-1; pos1_3 >= gi; --pos1_3) {//i->p
        p_3 = *pos1_3;
        p_to_3 = p_3.to;
        if(p_to_3 <= i || visit_3[p_to_3]) continue;
        p_je_3=p_3.je;
        visit_3[p_to_3] = true;
        n1_3 = outDegrees[p_to_3];
        if(n1_3==0) continue;
        auto gp = G_O1[p_to_3];
        end2_3 = gp + n1_3;
        for (pos2_3=end2_3-1; pos2_3 >= gp; --pos2_3) {
            q_3 = *pos2_3;
            q_to_3 = q_3.to;
            if (q_to_3 <= i || visit_3[q_to_3])continue;
            q_je_3 = q_3.je;
#ifdef JEJUDGE
            judge_3 = 1.0 * q_je_3 / p_je_3;
            if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
            visit_3[q_to_3] = true;
            n2_3 = outDegrees[q_to_3];
            if (n2_3 == 0) continue;
            auto gq = G_O1[q_to_3];
            end3_3 = gq + n2_3;
            for (pos3_3 = end3_3-1; pos3_3 >= gq; --pos3_3) {//i-p-q
                r_3 = *pos3_3;
                r_to_3 = r_3.to;
                if (r_to_3 < i || visit_3[r_to_3]) continue;
                r_je_3 = r_3.je;
#ifdef JEJUDGE
                judge_3 = 1.0 * r_je_3/q_je_3;
                if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                if(r_to_3==i){
                    judge_3 = 1.0 * p_je_3 / r_je_3;
                    if(judge_3<MINJE || judge_3>MAXJE) continue;
                    auto res=idsLF[q_to_3];
                    ans3p_3 -= strsz[q_to_3];
                    memcpy(ans3p_3, res, strsz[q_to_3]);
                    res = idsComma[p_to_3];
                    ans3p_3 -= strsz[p_to_3];
                    memcpy(ans3p_3, res, strsz[p_to_3]);
                    res =idsComma[i];
                    ans3p_3 -= strsz[i];
                    memcpy(ans3p_3, res, strsz[i]);
                    cnt1_3++;
                    continue;
                }
                visit_3[r_to_3] = true;
                n3_3 = outDegrees[r_to_3];
                if (n3_3 == 0) continue;
                auto gr = G_O1[r_to_3];
                end4_3 = gr + n3_3;
                for (pos4_3 = end4_3-1; pos4_3 >= gr; --pos4_3) {//begin remove node
                    s_3 = *pos4_3;//i-p-q-r-s
                    s_to_3 = s_3.to;
                    if (s_to_3 < i || visit_3[s_to_3]) continue;
                    s_je_3 = s_3.je;
#ifdef JEJUDGE
                    judge_3 = 1.0 * s_je_3/r_je_3;
                    if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                    if(s_to_3 == i){
                        judge_3 = 1.0 * p_je_3 / s_je_3;
                        if(judge_3<MINJE || judge_3>MAXJE) continue;
                        auto res = idsLF[r_to_3];
                        ans4p_3 -= strsz[r_to_3];
                        memcpy(ans4p_3, res, strsz[r_to_3]);
                        res=idsComma[q_to_3];
                        ans4p_3 -= strsz[q_to_3];
                        memcpy(ans4p_3, res, strsz[q_to_3]);
                        res = idsComma[p_to_3];
                        ans4p_3 -= strsz[p_to_3];
                        memcpy(ans4p_3, res, strsz[p_to_3]);
                        res =idsComma[i];
                        ans4p_3 -= strsz[i];
                        memcpy(ans4p_3, res, strsz[i]);
                        cnt2_3++;
                        continue;
                    }
                    visit_3[s_to_3]=true;
                    n4_3 = outDegrees[s_to_3];
                    if(n4_3==0)continue;
                    auto gs = G_O1[s_to_3];
                    end5_3 = gs + n4_3;
                    for(pos5_3=end5_3-1; pos5_3>=gs; --pos5_3){
                        t_3 = *pos5_3;
                        t_to_3 = t_3.to;
                        if(t_to_3 <i ||visit_3[t_to_3]||distancej_3[t_to_3]>3) continue;
                        t_je_3 = t_3.je;
                        //(s)-t-u-i不需要再判断内部节点
                        judge_3 = 1.0 * t_je_3 / s_je_3;
                        if(judge_3<MINJE || judge_3>MAXJE) continue;
                        if(t_to_3 == i){
                            judge_3 = 1.0 * p_je_3 / t_je_3;
                            if(judge_3<MINJE || judge_3>MAXJE) continue;
                            auto res=idsLF[s_to_3];
                            ans5p_3 -= strsz[s_to_3];
                            memcpy(ans5p_3, res, strsz[s_to_3]);
                            res=idsComma[r_to_3];
                            ans5p_3 -= strsz[r_to_3];
                            memcpy(ans5p_3, res, strsz[r_to_3]);
                            res=idsComma[q_to_3];
                            ans5p_3 -= strsz[q_to_3];
                            memcpy(ans5p_3, res, strsz[q_to_3]);
                            res = idsComma[p_to_3];
                            ans5p_3 -= strsz[p_to_3];
                            memcpy(ans5p_3, res, strsz[p_to_3]);
                            res =idsComma[i];
                            ans5p_3 -= strsz[i];
                            memcpy(ans5p_3, res, strsz[i]);
                            cnt3_3++;
                            continue;
                        }
                        visit_3[t_to_3] = true;
                        n5_3 = outDegrees[t_to_3];
                        if(n5_3==0)continue;
                        auto gt = G_O1[t_to_3];
                        end6_3 = gt + n5_3;
                        for(pos6_3 = end6_3-1; pos6_3>=gt; --pos6_3){
                            u_3 = *pos6_3;
                            u_to_3 = u_3.to;
                            if(u_to_3 <i ||visit_3[u_to_3]||distancej_3[u_to_3]>2) continue;
                            u_je_3 = u_3.je;
                            judge_3 = 1.0 * u_je_3 / t_je_3;
                            if(judge_3<MINJE || judge_3>MAXJE) continue;
                            if(u_to_3 == i){
                                judge_3 = 1.0 * p_je_3 / u_je_3;
                                if(judge_3<MINJE || judge_3>MAXJE) continue;
                                auto res=idsLF[t_to_3];
                                ans6p_3 -= strsz[t_to_3];
                                memcpy(ans6p_3, res, strsz[t_to_3]);
                                res=idsComma[s_to_3];
                                ans6p_3 -= strsz[s_to_3];
                                memcpy(ans6p_3, res, strsz[s_to_3]);
                                res=idsComma[r_to_3];
                                ans6p_3 -= strsz[r_to_3];
                                memcpy(ans6p_3, res, strsz[r_to_3]);
                                res=idsComma[q_to_3];
                                ans6p_3 -= strsz[q_to_3];
                                memcpy(ans6p_3, res, strsz[q_to_3]);
                                res = idsComma[p_to_3];
                                ans6p_3 -= strsz[p_to_3];
                                memcpy(ans6p_3, res, strsz[p_to_3]);
                                res =idsComma[i];
                                ans6p_3 -= strsz[i];
                                memcpy(ans6p_3, res, strsz[i]);
                                cnt4_3++;
                                continue;
                            }
                            visit_3[u_to_3] = true;
                            auto gu = G_O1[u_to_3];
                            end7_3 = gu+outDegrees[u_to_3];
                            for(pos7_3=end7_3-1; pos7_3>=gu;--pos7_3){
                                v_3 = *pos7_3;
                                v_to_3 = v_3.to;
                                v_je_3 = v_3.je;
                                if (v_to_3 <i ||visit_3[v_to_3]||distancej_3[v_to_3]>1) continue;
                                judge_3 = 1.0*v_je_3/u_je_3;
                                if(judge_3<MINJE || judge_3>MAXJE) continue;
                                if(v_to_3==i) {
                                    judge_3 = 1.0 * p_je_3 / v_je_3;
                                    if (judge_3 < MINJE || judge_3 > MAXJE) continue;
                                    auto res = idsLF[u_to_3];
                                    ans7p_3 -= strsz[u_to_3];
                                    memcpy(ans7p_3, res, strsz[u_to_3]);
                                    res = idsComma[t_to_3];
                                    ans7p_3 -= strsz[t_to_3];
                                    memcpy(ans7p_3, res, strsz[t_to_3]);
                                    res = idsComma[s_to_3];
                                    ans7p_3 -= strsz[s_to_3];
                                    memcpy(ans7p_3, res, strsz[s_to_3]);
                                    res = idsComma[r_to_3];
                                    ans7p_3 -= strsz[r_to_3];
                                    memcpy(ans7p_3, res, strsz[r_to_3]);
                                    res = idsComma[q_to_3];
                                    ans7p_3 -= strsz[q_to_3];
                                    memcpy(ans7p_3, res, strsz[q_to_3]);
                                    res = idsComma[p_to_3];
                                    ans7p_3 -= strsz[p_to_3];
                                    memcpy(ans7p_3, res, strsz[p_to_3]);
                                    res = idsComma[i];
                                    ans7p_3 -= strsz[i];
                                    memcpy(ans7p_3, res, strsz[i]);
                                    cnt5_3++;
                                }
                                auto gv = G_O1[v_to_3];
                                end8_3 = gv+outDegrees[v_to_3];
                                for(pos8_3=end8_3-1;pos8_3>=gv;--pos8_3){
                                    w_3 = *pos8_3;
                                    if (w_3.to != i) continue;
                                    judge_3 = 1.0*w_3.je/v_je_3;
                                    if(judge_3<MINJE || judge_3>MAXJE) continue;
                                    judge_3 =1.0*p_je_3/w_3.je;
                                    if(judge_3<MINJE || judge_3>MAXJE) continue;
                                    auto res = idsLF[v_to_3];
                                    ans8p_3 -= strsz[v_to_3];
                                    memcpy(ans8p_3, res, strsz[v_to_3]);
                                    res = idsComma[u_to_3];
                                    ans8p_3 -= strsz[u_to_3];
                                    memcpy(ans8p_3, res, strsz[u_to_3]);
                                    res = idsComma[t_to_3];
                                    ans8p_3 -= strsz[t_to_3];
                                    memcpy(ans8p_3, res, strsz[t_to_3]);
                                    res = idsComma[s_to_3];
                                    ans8p_3 -= strsz[s_to_3];
                                    memcpy(ans8p_3, res, strsz[s_to_3]);
                                    res = idsComma[r_to_3];
                                    ans8p_3 -= strsz[r_to_3];
                                    memcpy(ans8p_3, res, strsz[r_to_3]);
                                    res = idsComma[q_to_3];
                                    ans8p_3 -= strsz[q_to_3];
                                    memcpy(ans8p_3, res, strsz[q_to_3]);
                                    res = idsComma[p_to_3];
                                    ans8p_3 -= strsz[p_to_3];
                                    memcpy(ans8p_3, res, strsz[p_to_3]);
                                    res = idsComma[i];
                                    ans8p_3 -= strsz[i];
                                    memcpy(ans8p_3, res, strsz[i]);
                                    cnt6_3++;
                                }
                            }
                            visit_3[u_to_3] = false;
                        }
                        visit_3[t_to_3] = false;
                    }
                    visit_3[s_to_3]=false;
                }
                visit_3[r_to_3] = false;
            }
            visit_3[q_to_3] = false;
        }
        visit_3[p_to_3] = false;
    }
}
inline void solve() {
    ans3p = ans3;
    ans4p = ans4;
    ans5p = ans5;
    ans6p = ans6;
    ans7p = ans7;
    ans8p = ans8;
    visit = (bool *) malloc(nodecnt * sizeof(bool));
    memset(visit, 0, sizeof(bool) * nodecnt);
    uint32_t n1t, n2t, n3t;
    Node k{}, j{}, tt1{};
    Node *a, *b, *c;
    Node *end1t, *end2t, *end3t;
    bool flag_m = false;
    while (true) {
        pthread_mutex_lock(&mutex1_2);
        if (e1 - s1 <= 1)flag_m = true;
        s1++;
        pthread_mutex_unlock(&mutex1_2);
        if (flag_m)break;
        uint32_t i = s1;
        if (!outDegrees[i] || !inDegrees[i]) continue;
        for(uint32_t xx=0;xx<nodecnt;xx++){
            distancej[xx]=4;
        }
        distancej[i]=0;
        auto &gi = G_I1[i];
        n1t = inDegrees[i];
        end1t = n1t + gi;
        for (a = gi; a < end1t; a++) {
            k = *a;
            k_to = k.to;
            if (k_to <= i) continue;
            if(distancej[k_to]>1) distancej[k_to] = 1;
            auto &gk = G_I1[k_to];
            n2t = inDegrees[k_to];
            if (n2t == 0) continue;
            end2t = n2t + gk;

            for (b = gk; b < end2t; b++) {//j->k->i
                j = *b;
                j_to = j.to;
                if (j_to <= i) continue;
#ifdef JEJUDGE_REVERSE
                judge = 1.0 * k.je / j.je;
                if (judge < MINJE || judge > MAXJE) continue;
#endif
                if(distancej[j_to]>2) distancej[j_to] = 2;
                auto &gj = G_I1[j_to];
                n3t = inDegrees[j_to];
                if (n3t == 0)continue;
                end3t = n3t + gj;
                for (c = gj; c < end3t; c++) {//t-j-k-i
                    tt1 = *c;
                    tt_to = tt1.to;
                    if (tt_to <= i||tt_to==k_to)continue;
#ifdef JEJUDGE_REVERSE
                    judge = 1.0 * j.je / tt1.je;
                    if (judge < MINJE || judge > MAXJE) continue;
#endif
                    distanceje[k_to] = k.je;
                    if(distancej[tt_to]==4) distancej[tt_to] = 3;
                }
            }
        }
        dfs(i);
    }

}
inline void solve1() {
    ans3_1[MAX_SIZE_3_1 - 1] = '\0';
    ans4_1[MAX_SIZE_4_1 - 1] = '\0';
    ans5_1[MAX_SIZE_5_1 - 1] = '\0';
    ans6_1[MAX_SIZE_6_1 - 1] = '\0';
    ans7_1[MAX_SIZE_7_1 - 1] = '\0';
    ans8_1[MAX_SIZE_8_1 - 1] = '\0';
    ans3p_1 = ans3_1 + MAX_SIZE_3_1 - 1;
    ans4p_1 = ans4_1 + MAX_SIZE_4_1 - 1;
    ans5p_1 = ans5_1 + MAX_SIZE_5_1 - 1;
    ans6p_1 = ans6_1 + MAX_SIZE_6_1 - 1;
    ans7p_1 = ans7_1 + MAX_SIZE_7_1 - 1;
    ans8p_1 = ans8_1 + MAX_SIZE_8_1 - 1;
    visit_1 = (bool *) malloc(nodecnt * sizeof(bool));
    memset(visit_1, 0, sizeof(bool) * nodecnt);
    uint32_t n1t, n2t, n3t;
    Node k{}, j{}, tt1{};
    Node *a, *b, *c;
    Node *end1t, *end2t, *end3t;
    bool flag_m = false;
    while (true) {
        pthread_mutex_lock(&mutex1_2);
        if (e1 - s1 <= 1)flag_m = true;
        e1--;
        pthread_mutex_unlock(&mutex1_2);
        if (flag_m)break;
        uint32_t i = e1;
        if (!outDegrees[i] || !inDegrees[i]) continue;
        for(uint32_t xx=0;xx<nodecnt;xx++){
            distancej_1[xx]=4;
        }
        distancej_1[i]=0;
        auto &gi = G_I1[i];
        n1t = inDegrees[i];
        end1t = n1t + gi;
        for (a = gi; a < end1t; a++) {
            k = *a;
            k_to_1 = k.to;
            if (k_to_1 <= i) continue;
            if(distancej_1[k_to_1]>1) distancej_1[k_to_1] = 1;
            auto &gk = G_I1[k_to_1];
            n2t = inDegrees[k_to_1];
            if (n2t == 0) continue;
            end2t = n2t + gk;

            for (b = gk; b < end2t; b++) {//j->k->i
                j = *b;
                j_to_1 = j.to;
                if (j_to_1 <= i) continue;
#ifdef JEJUDGE_REVERSE
                judge_1 = 1.0 * k.je / j.je;
                if (judge_1 < MINJE || judge_1 > MAXJE) continue;
#endif
                if(distancej_1[j_to_1]>2) distancej_1[j_to_1] = 2;
                auto &gj = G_I1[j_to_1];
                n3t = inDegrees[j_to_1];
                if (n3t == 0)continue;
                end3t = n3t + gj;
                for (c = gj; c < end3t; c++) {//t-j-k-i
                    tt1 = *c;
                    tt_to_1 = tt1.to;
                    if (tt_to_1 <= i||tt_to_1==k_to_1)continue;
#ifdef JEJUDGE_REVERSE
                    judge_1 = 1.0 * j.je / tt1.je;
                    if (judge_1 < MINJE || judge_1 > MAXJE) continue;
#endif
                    distanceje_1[k_to_1] = k.je;
                    if(distancej_1[tt_to_1]==4) distancej_1[tt_to_1] = 3;
                }
            }
        }
        dfs_1(i);
    }
}
inline void solve2() {
    ans3p_2 = ans3_2;
    ans4p_2 = ans4_2;
    ans5p_2 = ans5_2;
    ans6p_2 = ans6_2;
    ans7p_2 = ans7_2;
    ans8p_2 = ans8_2;
    visit_2 = (bool *) malloc(nodecnt * sizeof(bool));
    memset(visit_2, 0, sizeof(bool) * nodecnt);
    uint32_t n1t, n2t, n3t;
    Node k{}, j{}, tt1{};
    Node *a, *b, *c;
    Node *end1t, *end2t, *end3t;
    bool flag_m = false;
    while (true) {
        pthread_mutex_lock(&mutex3_4);
        if (e2 - s2 <= 1)flag_m = true;
        s2++;
        pthread_mutex_unlock(&mutex3_4);
        if (flag_m)break;
        uint32_t i = s2;
        if (!outDegrees[i] || !inDegrees[i]) continue;
        for(uint32_t xx=0;xx<nodecnt;xx++){
            distancej_2[xx]=4;
        }
        distancej_2[i]=0;
        auto &gi = G_I1[i];
        n1t = inDegrees[i];
        end1t = n1t + gi;
        for (a = gi; a < end1t; a++) {
            k = *a;
            k_to_2 = k.to;
            if (k_to_2 <= i) continue;
            if(distancej_2[k_to_2]>1) distancej_2[k_to_2] = 1;
            auto &gk = G_I1[k_to_2];
            n2t = inDegrees[k_to_2];
            if (n2t == 0) continue;
            end2t = n2t + gk;

            for (b = gk; b < end2t; b++) {//j->k->i
                j = *b;
                j_to_2 = j.to;
                if (j_to_2 <= i) continue;
#ifdef JEJUDGE_REVERSE
                judge_2 = 1.0 * k.je / j.je;
                if (judge_2 < MINJE || judge_2 > MAXJE) continue;
#endif
                if(distancej_2[j_to_2]>2) distancej_2[j_to_2] = 2;
                auto &gj = G_I1[j_to_2];
                n3t = inDegrees[j_to_2];
                if (n3t == 0)continue;
                end3t = n3t + gj;
                for (c = gj; c < end3t; c++) {//t-j-k-i
                    tt1 = *c;
                    tt_to_2 = tt1.to;
                    if (tt_to_2 <= i||tt_to_2==k_to_2)continue;
#ifdef JEJUDGE_REVERSE
                    judge_2 = 1.0 * j.je / tt1.je;
                    if (judge_2 < MINJE || judge_2 > MAXJE) continue;
#endif
                    distanceje_2[k_to_2] = k.je;
                    if(distancej_2[tt_to_2]==4) distancej_2[tt_to_2] = 3;
                }
            }
        }
        dfs_2(i);
    }

}
inline void solve3() {
    ans3_3[MAX_SIZE_3_2 - 1] = '\0';
    ans4_3[MAX_SIZE_4_2 - 1] = '\0';
    ans5_3[MAX_SIZE_5_2 - 1] = '\0';
    ans6_3[MAX_SIZE_6_2 - 1] = '\0';
    ans7_3[MAX_SIZE_7_2 - 1] = '\0';
    ans8_3[MAX_SIZE_8_2 - 1] = '\0';
    ans3p_3 = ans3_3 + MAX_SIZE_3_2 - 1;
    ans4p_3 = ans4_3 + MAX_SIZE_4_2 - 1;
    ans5p_3 = ans5_3 + MAX_SIZE_5_2 - 1;
    ans6p_3 = ans6_3 + MAX_SIZE_6_2 - 1;
    ans7p_3 = ans7_3 + MAX_SIZE_7_2 - 1;
    ans8p_3 = ans8_3 + MAX_SIZE_8_2 - 1;
    visit_3 = (bool *) malloc(nodecnt * sizeof(bool));
    memset(visit_3 , 0, sizeof(bool) * nodecnt);
    uint32_t n1t, n2t, n3t;
    Node k{}, j{}, tt1{};
    Node *a, *b, *c;
    Node *end1t, *end2t, *end3t;
    bool flag_m = false;
    while (true) {
        pthread_mutex_lock(&mutex3_4);
        if (e2 - s2 <= 1)flag_m = true;
        e2--;
        pthread_mutex_unlock(&mutex3_4);
        if (flag_m)break;
        uint32_t i = e2;
        if (!outDegrees[i] || !inDegrees[i]) continue;
        for(uint32_t xx=0;xx<nodecnt;xx++){
            distancej_3[xx]=4;
        }
        distancej_3[i]=0;
        auto &gi = G_I1[i];
        n1t = inDegrees[i];
        end1t = n1t + gi;
        for (a = gi; a < end1t; a++) {
            k = *a;
            k_to_3 = k.to;
            if (k_to_3 <= i) continue;
            if(distancej_3[k_to_3]>1) distancej_3[k_to_3] = 1;
            auto &gk = G_I1[k_to_3];
            n2t = inDegrees[k_to_3];
            if (n2t == 0) continue;
            end2t = n2t + gk;

            for (b = gk; b < end2t; b++) {//j->k->i
                j = *b;
                j_to_3 = j.to;
                if (j_to_3 <= i) continue;
#ifdef JEJUDGE_REVERSE
                judge_3 = 1.0 * k.je / j.je;
                if (judge_3 < MINJE || judge_3 > MAXJE) continue;
#endif
                if(distancej_3[j_to_3]>2) distancej_3[j_to_3] = 2;
                auto &gj = G_I1[j_to_3];
                n3t = inDegrees[j_to_3];
                if (n3t == 0)continue;
                end3t = n3t + gj;
                for (c = gj; c < end3t; c++) {//t-j-k-i
                    tt1 = *c;
                    tt_to_3 = tt1.to;
                    if (tt_to_3 <= i||tt_to_3==k_to_3)continue;
#ifdef JEJUDGE_REVERSE
                    judge_3 = 1.0 * j.je / tt1.je;
                    if (judge_3 < MINJE || judge_3 > MAXJE) continue;
#endif
                    distanceje_3[k_to_3] = k.je;
                    if(distancej_3[tt_to_3]==4) distancej_3[tt_to_3] = 3;
                }
            }
        }
        dfs_3(i);
    }

}
inline void save_fwrite_buf(const char *outputFile){
    int ansCnt_=0;
    ansCnt_+=cnt1;
    ansCnt_+=cnt2;
    ansCnt_+=cnt3;
    ansCnt_+=cnt4;
    ansCnt_+=cnt5;
    ansCnt_+=cnt6;

    ansCnt_+=cnt1_1;
    ansCnt_+=cnt2_1;
    ansCnt_+=cnt3_1;
    ansCnt_+=cnt4_1;
    ansCnt_+=cnt5_1;
    ansCnt_+=cnt6_1;

    ansCnt_+=cnt1_2;
    ansCnt_+=cnt2_2;
    ansCnt_+=cnt3_2;
    ansCnt_+=cnt4_2;
    ansCnt_+=cnt5_2;
    ansCnt_+=cnt6_2;

    ansCnt_+=cnt1_3;
    ansCnt_+=cnt2_3;
    ansCnt_+=cnt3_3;
    ansCnt_+=cnt4_3;
    ansCnt_+=cnt5_3;
    ansCnt_+=cnt6_3;

    c_len1 = ans3p - ans3;
    c_len2 = ans4p - ans4;
    c_len3 = ans5p - ans5;
    c_len4 = ans6p - ans6;
    c_len5 = ans7p - ans7;
    c_len6 = ans8p - ans8;

    c_len1_1 = ans3_1 + MAX_SIZE_3_1 - ans3p_1 - 1;
    c_len2_1 = ans4_1 + MAX_SIZE_4_1 - ans4p_1 - 1;
    c_len3_1 = ans5_1 + MAX_SIZE_5_1 - ans5p_1 - 1;
    c_len4_1 = ans6_1 + MAX_SIZE_6_1 - ans6p_1 - 1;
    c_len5_1 = ans7_1 + MAX_SIZE_7_1 - ans7p_1 - 1;
    c_len6_1 = ans8_1 + MAX_SIZE_8_1 - ans8p_1 - 1;

    c_len1_2 = ans3p_2 - ans3_2;
    c_len2_2 = ans4p_2 - ans4_2;
    c_len3_2 = ans5p_2 - ans5_2;
    c_len4_2 = ans6p_2 - ans6_2;
    c_len5_2 = ans7p_2 - ans7_2;
    c_len6_2 = ans8p_2 - ans8_2;

    c_len1_3 = ans3_3 + MAX_SIZE_3_2 - ans3p_3 - 1;
    c_len2_3 = ans4_3 + MAX_SIZE_4_2 - ans4p_3 - 1;
    c_len3_3 = ans5_3 + MAX_SIZE_5_2 - ans5p_3 - 1;
    c_len4_3 = ans6_3 + MAX_SIZE_6_2 - ans6p_3 - 1;
    c_len5_3 = ans7_3 + MAX_SIZE_7_2 - ans7p_3 - 1;
    c_len6_3 = ans8_3 + MAX_SIZE_8_2 - ans8p_3 - 1;

    ans3[c_len1] = '\0';
    ans4[c_len2] = '\0';
    ans5[c_len3] = '\0';
    ans6[c_len4] = '\0';
    ans7[c_len5] = '\0';
    ans8[c_len6] = '\0';

    ans3_2[c_len1_2] = '\0';
    ans4_2[c_len2_2] = '\0';
    ans5_2[c_len3_2] = '\0';
    ans6_2[c_len4_2] = '\0';
    ans7_2[c_len5_2] = '\0';
    ans8_2[c_len6_2] = '\0';

#ifdef TEST
    auto ts=clock();
#endif
    /**开始写**/
    FILE *fp = fopen(outputFile, "wb");
    string total = to_string(ansCnt_)+"\n";
    fwrite(total.c_str(), sizeof(char), total.size(), fp);
    /**写3环**/
    fwrite(ans3,sizeof(char),c_len1,fp);
    fwrite(ans3p_1,sizeof(char),c_len1_1,fp);
    fwrite(ans3_2,sizeof(char),c_len1_2,fp);
    fwrite(ans3p_3,sizeof(char),c_len1_3,fp);
    /**写4环**/
    fwrite(ans4,sizeof(char),c_len2,fp);
    fwrite(ans4p_1,sizeof(char),c_len2_1,fp);
    fwrite(ans4_2,sizeof(char),c_len2_2,fp);
    fwrite(ans4p_3,sizeof(char),c_len2_3,fp);
    /**写5环**/
    fwrite(ans5,sizeof(char),c_len3,fp);
    fwrite(ans5p_1,sizeof(char),c_len3_1,fp);
    fwrite(ans5_2,sizeof(char),c_len3_2,fp);
    fwrite(ans5p_3,sizeof(char),c_len3_3,fp);
    /**写6环**/
    fwrite(ans6,sizeof(char),c_len4,fp);
    fwrite(ans6p_1,sizeof(char),c_len4_1,fp);
    fwrite(ans6_2,sizeof(char),c_len4_2,fp);
    fwrite(ans6p_3,sizeof(char),c_len4_3,fp);
    /**写7环**/
    fwrite(ans7,sizeof(char),c_len5,fp);
    fwrite(ans7p_1,sizeof(char),c_len5_1,fp);
    fwrite(ans7_2,sizeof(char),c_len5_2,fp);
    fwrite(ans7p_3,sizeof(char),c_len5_3,fp);
    /**写7环**/
    fwrite(ans8,sizeof(char),c_len6,fp);
    fwrite(ans8p_1,sizeof(char),c_len6_1,fp);
    fwrite(ans8_2,sizeof(char),c_len6_2,fp);
    fwrite(ans8p_3,sizeof(char),c_len6_3,fp);
    fclose(fp);
#ifdef TEST
    cout<<"write time: "<<(clock()-ts)/CLOCKS_PER_SEC<<"s"<<endl;
     cout<<"total rings: "<<ansCnt_<<endl;
#endif
}
int main(){
#ifdef TEST
    auto ts=clock();
#endif
//    const char *test_file = "test_data_19630345.txt";
//    const char *test_file = "test_data.txt";
//    const char *outputFile = "result2.txt";
    const char * test_file= "/data/test_data.txt";
    const char * outputFile = "/projects/student/result.txt";
    Input_Graph(test_file);
    parseInput();
    topoSort();
#ifdef TEST
    cout<<"Read+Parse+Topo Time: "<<(clock()-ts)/CLOCKS_PER_SEC<<"s"<<endl;
#endif
    /**多线程共享区间配置**/
    /** 线程1和2共享区间[0, e1-1]*/
    s1 = -1;
    e1 = (int)(nodecnt * CS);
    /** 线程3和4共享区间[e1, nodecnt-1]*/
    s2 = e1 - 1;
    e2 = nodecnt;
    /**开始多线程**/
    thread threads[THREAD_NUM];
    threads[0] = thread(solve);
    threads[1] = thread(solve1);
    threads[2] = thread(solve2);
    threads[3] = thread(solve3);
    threads[0].join();
    threads[1].join();
    threads[2].join();
    threads[3].join();
    save_fwrite_buf(outputFile);
#ifdef TEST
    cout<<"All time:"<<(clock()-ts)/CLOCKS_PER_SEC<<"s"<<endl;
#endif
    return 0;
}