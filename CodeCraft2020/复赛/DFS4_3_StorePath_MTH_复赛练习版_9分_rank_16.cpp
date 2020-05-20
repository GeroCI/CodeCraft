#include<bits/stdc++.h>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
#define JEJUDGE
#define JEJUDGE_REVERSE
#define TEST
#define THREAD_NUM 4
//#define MAX_SIZE_7 1024 * 1024 * 300//300M的内存
//#define MAX_SIZE_6 1024 * 1024 * 100//100M的内存
//#define MAX_SIZE_5 1024 * 1024 * 50//50M的内存
//#define MAX_SIZE_4 1024 * 1024 * 40//40M的内存
//#define MAX_SIZE_3 1024 * 1024 * 30//30M的内存
#define MAX_SIZE_7 1024 * 1024 * 20//300M的内存
#define MAX_SIZE_6 1024 * 1024 * 10//100M的内存
#define MAX_SIZE_5 1024 * 1024 * 10//50M的内存
#define MAX_SIZE_4 1024 * 1024 * 10//40M的内存
#define MAX_SIZE_3 1024 * 1024 * 10//30M的内存
struct Node{
    uint32_t to{};
    uint32_t je{};
    Node()= default;
    void set(uint32_t &a, uint32_t &b){
        to =a;
        je =b;
    }
    Node(const Node &nd){//拷贝构造函数
        to = nd.to;
        je = nd.je;
    }
};
struct Node1{
    uint32_t to{};
    uint32_t je1{};
    uint32_t je2{};
    Node1()= default;
    void set(uint32_t &a,uint32_t &b,uint32_t &c){
        to = a;
        je1 = b;
        je2 = c;
    }
    Node1(const Node1 &nd){//拷贝构造函数
        to = nd.to;
        je1 = nd.je1;
        je2  = nd.je2;
    }
};
const double MINJE = 0.2;
const double MAXJE = 3.0;
const int MAX_E=2000000;
char **idsComma;
char **idsLF;
Node **G_O;
Node **G_I;
Node **G_O1;
Node **G_I1;
uint32_t *inDegrees;
uint32_t *outDegrees;
uint32_t *inDegrees_tmp;
uint32_t *outDegrees_tmp;
uint32_t *reslen;
int front=0,rear=0;
char buf_path[30];
uint32_t *que;
vector<uint32_t> inputs;
vector<uint32_t> inputs_id;
unordered_map<uint32_t , uint32_t> idHash;
unordered_map<uint32_t , uint32_t> reidHash;
uint32_t nodecnt = 0;

pthread_mutex_t mutex1_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3_4 = PTHREAD_MUTEX_INITIALIZER;

//#define TESTREAD
uint32_t s1,e1;
uint32_t s2,e2;
/**线程1参数**/
char ans3[MAX_SIZE_3];
char ans4[MAX_SIZE_4];
char ans5[MAX_SIZE_5];
char ans6[MAX_SIZE_6];
char ans7[MAX_SIZE_7];
char *ans3p;
char *ans4p;
char *ans5p;
char *ans6p;
char *ans7p;
Node1 qq,rr,ss,tt,uu;
double judge = 0.0;
uint32_t ss_to,qq_to,rr_to,tt_to,uu_to;
Node *path3_begin,*path3_end,*it3,*it4,*it5;
Node1 *itr2,*itr3,*itr4,*itr5,*itr6,*path2_begin,*path2_end;
uint32_t sz,sz1;
uint32_t k_to,j_to,*flag,flag1;
uint32_t *HashTB,*HashTB1;
uint32_t *reachable2;
uint32_t *reachable3;
uint32_t *nodeReLayer3;
Node1 **path2;
uint32_t *path2size;
uint32_t *path3size;
Node **path3;
uint32_t *visit;
int cnt1=0,cnt2=0,cnt3=0,cnt4=0,cnt5=0;
uint32_t c_len1=0,c_len2=0,c_len3=0,c_len4=0,c_len5=0;
int idx_1=0,idx_2=0;
Node *pos1, *pos2, *pos3, *pos4;
Node *end1, *end2, *end3, *end4;
uint32_t n1, n2, n3;
Node p, q, r, s, t, nd;
Node1 nd1;
uint32_t p_je,q_je,r_je,s_je,t_je;
uint32_t p_to,q_to,r_to,s_to,t_to;
/**线程2参数**/
char ans3_1[MAX_SIZE_3];
char ans4_1[MAX_SIZE_4];
char ans5_1[MAX_SIZE_5];
char ans6_1[MAX_SIZE_6];
char ans7_1[MAX_SIZE_7];
char *ans3p_1;
char *ans4p_1;
char *ans5p_1;
char *ans6p_1;
char *ans7p_1;
Node1 qq_1,rr_1,ss_1,tt_1,uu_1;
double judge_1 = 0.0;
uint32_t ss_to_1,qq_to_1,rr_to_1,tt_to_1,uu_to_1;
Node *path3_begin_1,*path3_end_1,*it3_1,*it4_1,*it5_1;
Node1 *itr2_1,*itr3_1,*itr4_1,*itr5_1,*itr6_1,*path2_begin_1,*path2_end_1;
uint32_t sz_1,sz1_1;
uint32_t k_to_1,j_to_1,*flag_1,flag1_1;
uint32_t *reachable2_1;
uint32_t *reachable3_1;
uint32_t *nodeReLayer3_1;
Node1 **path2_1;
uint32_t *path2size_1;
uint32_t *path3size_1;
Node **path3_1;
uint32_t *visit_1;
int cnt1_1=0,cnt2_1=0,cnt3_1=0,cnt4_1=0,cnt5_1=0;
uint32_t c_len1_1=0,c_len2_1=0,c_len3_1=0,c_len4_1=0,c_len5_1=0;
Node *pos1_1, *pos2_1, *pos3_1, *pos4_1;
Node *end1_1, *end2_1, *end3_1, *end4_1;
uint32_t n1_1, n2_1, n3_1;
Node p_1, q_1, r_1, s_1, t_1, nd_1;
Node1 nd1_1;
uint32_t p_je_1,q_je_1,r_je_1,s_je_1,t_je_1;
uint32_t p_to_1,q_to_1,r_to_1,s_to_1,t_to_1;
/**线程3参数**/
char ans3_2[MAX_SIZE_3];
char ans4_2[MAX_SIZE_4];
char ans5_2[MAX_SIZE_5];
char ans6_2[MAX_SIZE_6];
char ans7_2[MAX_SIZE_7];
char *ans3p_2;
char *ans4p_2;
char *ans5p_2;
char *ans6p_2;
char *ans7p_2;
Node1 qq_2,rr_2,ss_2,tt_2,uu_2;
double judge_2 = 0.0;
uint32_t ss_to_2,qq_to_2,rr_to_2,tt_to_2,uu_to_2;
Node *path3_begin_2,*path3_end_2,*it3_2,*it4_2,*it5_2;
Node1 *itr2_2,*itr3_2,*itr4_2,*itr5_2,*itr6_2,*path2_begin_2,*path2_end_2;
uint32_t sz_2,sz1_2;
uint32_t k_to_2,j_to_2,*flag_2,flag1_2;
uint32_t *reachable2_2;
uint32_t *reachable3_2;
uint32_t *nodeReLayer3_2;
Node1 **path2_2;
uint32_t *path2size_2;
uint32_t *path3size_2;
Node **path3_2;
uint32_t *visit_2;
int cnt1_2=0,cnt2_2=0,cnt3_2=0,cnt4_2=0,cnt5_2=0;
uint32_t c_len1_2=0,c_len2_2=0,c_len3_2=0,c_len4_2=0,c_len5_2=0;
Node *pos1_2, *pos2_2, *pos3_2, *pos4_2;
Node *end1_2, *end2_2, *end3_2, *end4_2;
uint32_t n1_2, n2_2, n3_2;
Node p_2, q_2, r_2, s_2, t_2, nd_2;
Node1 nd1_2;
uint32_t p_je_2,q_je_2,r_je_2,s_je_2,t_je_2;
uint32_t p_to_2,q_to_2,r_to_2,s_to_2,t_to_2;
/**线程4参数**/
char ans3_3[MAX_SIZE_3];
char ans4_3[MAX_SIZE_4];
char ans5_3[MAX_SIZE_5];
char ans6_3[MAX_SIZE_6];
char ans7_3[MAX_SIZE_7];
char *ans3p_3;
char *ans4p_3;
char *ans5p_3;
char *ans6p_3;
char *ans7p_3;
Node1 qq_3,rr_3,ss_3,tt_3,uu_3;
double judge_3 = 0.0;
uint32_t ss_to_3,qq_to_3,rr_to_3,tt_to_3,uu_to_3;
Node *path3_begin_3,*path3_end_3,*it3_3,*it4_3,*it5_3;
Node1 *itr2_3,*itr3_3,*itr4_3,*itr5_3,*itr6_3,*path2_begin_3,*path2_end_3;
uint32_t sz_3,sz1_3;
uint32_t k_to_3,j_to_3,*flag_3,flag1_3;
uint32_t *reachable2_3;
uint32_t *reachable3_3;
uint32_t *nodeReLayer3_3;
Node1 **path2_3;
uint32_t *path2size_3;
uint32_t *path3size_3;
Node **path3_3;
uint32_t *visit_3;
int cnt1_3=0,cnt2_3=0,cnt3_3=0,cnt4_3=0,cnt5_3=0;
uint32_t c_len1_3=0,c_len2_3=0,c_len3_3=0,c_len4_3=0,c_len5_3=0;
Node *pos1_3, *pos2_3, *pos3_3, *pos4_3;
Node *end1_3, *end2_3, *end3_3, *end4_3;
uint32_t n1_3, n2_3, n3_3;
Node p_3, q_3, r_3, s_3, t_3, nd_3;
Node1 nd1_3;
uint32_t p_je_3,q_je_3,r_je_3,s_je_3,t_je_3;
uint32_t p_to_3,q_to_3,r_to_3,s_to_3,t_to_3;

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
    inputs.reserve(MAX_E);
    inputs_id.reserve(MAX_E*2);
    for(;addr && addr!=e;addr++) {
        if(*addr==','){
            inputs_id.push_back(t1);
            t1=0;
            continue;
        }
        if(*addr=='\n'){
            inputs.push_back(t1);
            t1=0;
            continue;
        }
        if(*addr!='\r') t1 = t1 * 10 + *addr - '0';
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
void parseInput(){
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
    reslen = (uint32_t*)malloc(nodecnt* sizeof(uint32_t));
    memset(reslen,0,sizeof(uint32_t)*nodecnt);
    G_O = (Node**)malloc(sizeof(Node*) * nodecnt);
    G_O1 = (Node**)malloc(sizeof(Node*) * nodecnt);
    G_I1 = (Node**)malloc(sizeof(Node*) * nodecnt);



#ifdef TEST
    printf("%d Nodes in Total\n", nodecnt);
#endif
    uint32_t *p_out;
    Node **g_o;
    int szs = inputs.size();
    uint32_t idx;
    for (int i = 0; i < szs; i += 1) {
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
            *g_o=(Node*)malloc(128*sizeof(Node));
        }else{//访问过
            switch ((*p_out+1)&127) {
                case 0:{
                    *g_o = (Node*)realloc(*g_o,(*p_out+128)*sizeof(Node));
                    break;
                }
            }
        }
        (*g_o)[*p_out]=nd;
        (*p_out)++;
        inDegrees[ed]++;
    }
    free(HashTB);
    path3 = (Node**)malloc(sizeof(Node*) * nodecnt);
    path2 = (Node1**)malloc(sizeof(Node1*) * nodecnt);
    path2size = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(path2size,0,sizeof(uint32_t) * nodecnt);
    path3size = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(path3size,0,sizeof(uint32_t) * nodecnt);

    path3_1 = (Node**)malloc(sizeof(Node*) * nodecnt);
    path2_1 = (Node1**)malloc(sizeof(Node1*) * nodecnt);
    path2size_1 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(path2size_1, 0, sizeof(uint32_t) * nodecnt);
    path3size_1 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(path3size_1, 0, sizeof(uint32_t) * nodecnt);

    path3_2 = (Node**)malloc(sizeof(Node*) * nodecnt);
    path2_2 = (Node1**)malloc(sizeof(Node1*) * nodecnt);
    path2size_2 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(path2size_2, 0, sizeof(uint32_t) * nodecnt);
    path3size_2 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(path3size_2, 0, sizeof(uint32_t) * nodecnt);

    path3_3 = (Node**)malloc(sizeof(Node*) * nodecnt);
    path2_3 = (Node1**)malloc(sizeof(Node1*) * nodecnt);
    path2size_3 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(path2size_3, 0, sizeof(uint32_t) * nodecnt);
    path3size_3 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(path3size_3, 0, sizeof(uint32_t) * nodecnt);
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
                    *g_i=(Node*)malloc(128*sizeof(Node));
                }else{
                    switch ((*p_in+1)&127) {
                        case 0:{
                            *g_i = (Node*)realloc(*g_i,(*p_in+128)*sizeof(Node));
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

    reachable2 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(reachable2,0,sizeof(uint32_t)*nodecnt);
    reachable3 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(reachable3,0,sizeof(uint32_t)*nodecnt);

    reachable2_1 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(reachable2_1,0,sizeof(uint32_t)*nodecnt);
    reachable3_1 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(reachable3_1,0,sizeof(uint32_t)*nodecnt);

    reachable2_2 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(reachable2_2,0,sizeof(uint32_t)*nodecnt);
    reachable3_2 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(reachable3_2,0,sizeof(uint32_t)*nodecnt);

    reachable2_3 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(reachable2_3,0,sizeof(uint32_t)*nodecnt);
    reachable3_3 = (uint32_t*)malloc(sizeof(uint32_t) * nodecnt);
    memset(reachable3_3,0,sizeof(uint32_t)*nodecnt);

    HashTB = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(HashTB,0,sizeof(uint32_t)*nodecnt);
    HashTB1 = (uint32_t*)malloc(nodecnt*sizeof(uint32_t));
    memset(HashTB1,0,sizeof(uint32_t)*nodecnt);
    //构造新的邻接表和逆邻接表(入度>0且出度>0)
    for(uint32_t itr=0;itr<nodecnt;itr++){
        if(outDegrees_tmp[itr]){//入度小于等于0时outDegree_tmp自动为0
            uint32_t tid = reidHash[itr];
            idx_1=sprintf(buf_path, "%d", tid);
            idx_2=idx_1;
            buf_path[idx_1++]=',';
            buf_path[idx_1]='\0';
            Comma = &idsComma[itr];
            *Comma = (char*)malloc(40*sizeof(char));
            strcpy(*Comma,buf_path);
            buf_path[idx_2++]='\n';
            buf_path[idx_2]='\0';
            LF = &idsLF[itr];
            *LF=(char*)malloc(40*sizeof(char));
            strcpy(*LF,buf_path);
            reslen[itr] = idx_2;
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
                    *g_o1=(Node*)malloc(128*sizeof(Node));
                }else{
                    switch ((*outP+1)&127) {
                        case 0:{
                            *g_o1 = (Node*)realloc(*g_o1,(*outP+128)*sizeof(Node));
                            break;
                        }
                    }
                }
                if(!HashTB1[itr]){//没访问过
                    HashTB1[itr] =1;
                    *g_i1=(Node*)malloc(128*sizeof(Node));
                }else{
                    switch ((*outP+1)&127) {
                        case 0:{
                            *g_i1 = (Node*)realloc(*g_i1,(*outP+128)*sizeof(Node));
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
inline void dfs(uint32_t i) {
    visit[i]=1;
    auto gi = G_O1[i];
    end1 = gi + outDegrees[i];
    for (pos1 = gi; pos1 < end1; ++pos1) {//i->p
        p = *pos1;
        p_to = p.to;
        if(p_to <= i || visit[p_to]) continue;
        p_je=p.je;
        if( reachable2[p_to] == i+1 ){//i->p->q->i->p
            sz = path2size[p_to];
            path2_begin = path2[p_to];
            path2_end = path2_begin +sz;
            for(itr2=path2_begin;itr2<path2_end;++itr2){
                qq = *itr2;
#ifdef JEJUDGE
                judge = 1.0 * p_je/qq.je1;
                if(judge<MINJE || judge>MAXJE) continue;
                judge = 1.0 * qq.je2/p_je;
                if(judge<MINJE || judge>MAXJE) continue;
#endif
//                    if(c_len1>=MAX3NUM){//超过就增加100万字节
//                        MAX3NUM+=add_len;
//                        ans3 = (char*)realloc(ans3,MAX3NUM);
//                    }
                qq_to = qq.to;
                auto res =idsComma[i];
                strcpy(ans3p,res);
                ans3p+=reslen[i];
                res = idsComma[p_to];
                strcpy(ans3p,res);
                ans3p+=reslen[p_to];
                res=idsLF[qq_to];
                strcpy(ans3p,res);
                ans3p+=reslen[qq_to];
                cnt1++;
            }
        }
        visit[p_to] = 1;
        n1 = outDegrees[p_to];
        if(n1==0) continue;
        auto gp = G_O1[p_to];
        end2 = gp + n1;
        for (pos2=gp; pos2 < end2; ++pos2) {
            q = *pos2;
            q_to = q.to;
            if (q_to<=i||visit[q_to])continue;
            q_je = q.je;
#ifdef JEJUDGE
            judge = 1.0 * q_je/p_je;
            if(judge<MINJE || judge>MAXJE) continue;
#endif
            if(reachable2[q_to]==i+1){
                sz = path2size[q_to];
                path2_begin = path2[q_to];
                path2_end = path2_begin+sz;
                for(itr3 = path2_begin; itr3<path2_end; ++itr3){//i->p->q->r->i
                    rr = *itr3;
                    if(rr.to == p_to)continue;
#ifdef JEJUDGE
                    judge = 1.0 * p_je/rr.je1;
                    if(judge<MINJE || judge>MAXJE) continue;
                    judge = 1.0 * rr.je2/q_je;
                    if(judge<MINJE || judge>MAXJE) continue;
#endif
//                        if(c_len2>=MAX4NUM){//超过就增加100万字节
//                            MAX4NUM+=add_len;
//                            ans4 = (char*)realloc(ans4,MAX4NUM);
//                        }
                    rr_to = rr.to;
                    auto res =idsComma[i];
                    strcpy(ans4p,res);
                    ans4p+=reslen[i];
                    res = idsComma[p_to];
                    strcpy(ans4p,res);
                    ans4p+=reslen[p_to];
                    res=idsComma[q_to];
                    strcpy(ans4p,res);
                    ans4p+=reslen[q_to];
                    res=idsLF[rr_to];
                    strcpy(ans4p,res);
                    ans4p+=reslen[rr_to];
                    cnt2++;
                }
            }
            if(reachable3[q_to]==i+1){
                visit[q_to]=1;
                sz= path3size[q_to];
                path3_begin = path3[q_to];
                path3_end = path3_begin+sz;
                for(it3 = path3_begin; it3<path3_end;++it3){
                    r = *it3;
                    r_to =r.to;
                    if(visit[r_to])continue;
#ifdef JEJUDGE
                    judge = 1.0 * r.je/q_je;
                    if(judge<MINJE || judge>MAXJE) continue;
#endif
                    sz1 = path2size[r_to];
                    path2_begin = path2[r_to];
                    path2_end = path2_begin+sz1;
                    for(itr4 = path2_begin; itr4<path2_end;++itr4){//i->p->q->r-s->i
                        ss = *itr4;
                        if(visit[ss.to])continue;

#ifdef JEJUDGE
                        judge = 1.0 * p_je/ss.je1;
                        if(judge<MINJE || judge>MAXJE) continue;
                        judge = 1.0 * ss.je2/r.je;
                        if(judge<MINJE || judge>MAXJE) continue;
#endif
//                            if(c_len3>=MAX5NUM){//超过就增加100万字节
//                                MAX5NUM+=add_len;
//                                ans5 = (char*)realloc(ans5,MAX5NUM);
//                            }
                        ss_to = ss.to;
                        auto res =idsComma[i];
                        strcpy(ans5p,res);
                        ans5p+=reslen[i];
                        res = idsComma[p_to];
                        strcpy(ans5p,res);
                        ans5p+=reslen[p_to];
                        res=idsComma[q_to];
                        strcpy(ans5p,res);
                        ans5p+=reslen[q_to];
                        res=idsComma[r_to];
                        strcpy(ans5p,res);
                        ans5p+=reslen[r_to];
                        res=idsLF[ss_to];
                        strcpy(ans5p,res);
                        ans5p+=reslen[ss_to];
                        cnt3++;
                    }
                }
                visit[q_to]=0;
            }
            visit[q_to] = 1;
            n2 = outDegrees[q_to];
            if(n2==0) continue;
            auto gq = G_O1[q_to];
            end3 = gq + n2;
            for (pos3=gq; pos3 < end3; ++pos3) {

                r = *pos3;
                r_to = r.to;
                if(r_to<=i||visit[r_to]) continue;
                r_je = r.je;
#ifdef JEJUDGE
                judge = 1.0 * r_je/q_je;
                if(judge<MINJE || judge>MAXJE) continue;
#endif
                if(reachable3[r_to]==i+1){
                    visit[r_to]=1;
                    sz = path3size[r_to];
                    path3_begin = path3[r_to];
                    path3_end = path3_begin+sz;
                    for(it4=path3_begin;it4<path3_end;++it4){
                        s = *it4;
                        s_to = s.to;
                        if(visit[s_to])continue;
#ifdef JEJUDGE
                        judge = 1.0 * s.je/r_je;
                        if(judge<MINJE || judge>MAXJE) continue;
#endif
                        sz1 = path2size[s_to];
                        path2_begin = path2[s_to];
                        path2_end = path2_begin + sz1;
                        for(itr5=path2_begin;itr5<path2_end;itr5++){//i->p->q->r-s-t->i
                            tt = *itr5;
                            if(visit[tt.to])continue;
#ifdef JEJUDGE
                            judge = 1.0 * p_je/tt.je1;
                            if(judge<MINJE || judge>MAXJE) continue;
                            judge = 1.0 * tt.je2/s.je;
                            if(judge<MINJE || judge>MAXJE) continue;
#endif
                            tt_to = tt.to;
                            auto res =idsComma[i];
                            strcpy(ans6p,res);
                            ans6p+=reslen[i];
                            res = idsComma[p_to];
                            strcpy(ans6p,res);
                            ans6p+=reslen[p_to];
                            res=idsComma[q_to];
                            strcpy(ans6p,res);
                            ans6p+=reslen[q_to];
                            res=idsComma[r_to];
                            strcpy(ans6p,res);
                            ans6p+=reslen[r_to];
                            res=idsComma[s_to];
                            strcpy(ans6p,res);
                            ans6p+=reslen[s_to];
                            res=idsLF[tt_to];
                            strcpy(ans6p,res);
                            ans6p+=reslen[tt_to];
                            cnt4++;
                        }
                    }
                    visit[r_to]=0;
                }
                visit[r_to] = 1;
                n3 = outDegrees[r_to];
                if(n3==0) continue;
                auto gr = G_O1[r_to];
                end4 = gr + n3;
                for (pos4=gr; pos4 < end4; pos4++) {
                    s = *pos4;
                    s_to = s.to;
                    if(s_to<=i||visit[s_to]) continue;
                    s_je = s.je;
#ifdef JEJUDGE
                    judge = 1.0 * s_je/r_je;
                    if(judge<MINJE || judge>MAXJE) continue;
#endif
                    if(reachable3[s_to]==i+1) {

                        visit[s_to] =1;
                        sz = path3size[s_to];
                        path3_begin = path3[s_to];
                        path3_end = path3_begin+sz;
                        for (it5 = path3_begin; it5 < path3_end; ++it5) {

                            t = *it5;
                            t_to = t.to;

                            if (visit[t_to])continue;
                            t_je = t.je;
#ifdef JEJUDGE
                            judge = 1.0 * t_je/s_je;
                            if(judge<MINJE || judge>MAXJE) continue;
#endif
                            sz1 = path2size[t_to];
                            path2_begin = path2[t_to];
                            path2_end = path2_begin+sz1;
                            for (itr6 = path2_begin; itr6 < path2_end; ++itr6) {//i->p->q->r->s->t->u->i
                                uu = *itr6;
                                if (visit[uu.to])continue;
#ifdef JEJUDGE
                                judge = 1.0 * p_je/uu.je1;
                                if(judge<MINJE || judge>MAXJE) continue;
                                judge = 1.0 * uu.je2/t.je;
                                if(judge<MINJE || judge>MAXJE) continue;
#endif
//                                    if(c_len5>=MAX7NUM){//超过就增加100万字节
//                                        MAX7NUM+=add_len;
//                                        ans7 = (char*)realloc(ans7,MAX7NUM);
//                                    }
                                uu_to = uu.to;
                                auto res = idsComma[i];
                                strcpy(ans7p, res);
                                ans7p += reslen[i];
                                res = idsComma[p_to];
                                strcpy(ans7p, res);
                                ans7p += reslen[p_to];
                                res = idsComma[q_to];
                                strcpy(ans7p, res);
                                ans7p += reslen[q_to];
                                res = idsComma[r_to];
                                strcpy(ans7p, res);
                                ans7p += reslen[r_to];
                                res = idsComma[s_to];
                                strcpy(ans7p, res);
                                ans7p += reslen[s_to];
                                res = idsComma[t_to];
                                strcpy(ans7p, res);
                                ans7p += reslen[t_to];
                                res = idsLF[uu_to];
                                strcpy(ans7p, res);
                                ans7p += reslen[uu_to];
                                cnt5++;
                            }

                        }
                        visit[s_to] = 0;
                    }
                }
                visit[r_to] = 0;
            }
            visit[q_to] = 0;
        }
        visit[p_to] = 0;
    }
    visit[i] = 0;
}
inline void dfs1(uint32_t i) {
    visit_1[i]=1;
    auto gi = G_O1[i];
    end1_1 = gi + outDegrees[i];
    for (pos1_1 = end1_1-1; pos1_1 >= gi; --pos1_1) {//i->p
        p_1 = *pos1_1;
        p_to_1 = p_1.to;
        if(p_to_1 <= i || visit_1[p_to_1]) continue;
        p_je_1=p_1.je;
        if( reachable2_1[p_to_1] == i+1 ){//i->p->q->i->p
            sz_1 = path2size_1[p_to_1];
            path2_begin_1 = path2_1[p_to_1];
            path2_end_1 = path2_begin_1 +sz_1;
            for(itr2_1=path2_end_1-1;itr2_1>=path2_begin_1;--itr2_1){
                qq_1 = *itr2_1;
#ifdef JEJUDGE
                judge_1 = 1.0 * p_je_1/qq_1.je1;
                if(judge_1<MINJE || judge_1>MAXJE) continue;
                judge_1 = 1.0 * qq_1.je2/p_je_1;
                if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                qq_to_1 = qq_1.to;
                auto res=idsLF[qq_to_1];
                ans3p_1 -= reslen[qq_to_1];
                strcpy(ans3p_1,res);
                res = idsComma[p_to_1];
                ans3p_1 -= reslen[p_to_1];
                strcpy(ans3p_1, res);
                res =idsComma[i];
                ans3p_1 -= reslen[i];
                strcpy(ans3p_1,res);
                cnt1_1++;
            }
        }
        visit_1[p_to_1] = 1;
        n1_1 = outDegrees[p_to_1];
        if(n1_1==0) continue;
        auto gp = G_O1[p_to_1];
        end2_1 = gp + n1_1;
        for (pos2_1=end2_1-1; pos2_1 >= gp; --pos2_1) {
            q_1 = *pos2_1;
            q_to_1 = q_1.to;
            if (q_to_1<=i||visit_1[q_to_1])continue;
            q_je_1 = q_1.je;
#ifdef JEJUDGE
            judge_1 = 1.0 * q_je_1/p_je_1;
            if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
            if(reachable2_1[q_to_1]==i+1){
                sz_1 = path2size_1[q_to_1];
                path2_begin_1 = path2_1[q_to_1];
                path2_end_1 = path2_begin_1+sz_1;
                for(itr3_1 = path2_end_1-1; itr3_1>=path2_begin_1; --itr3_1){//i->p->q->r->i
                    rr_1 = *itr3_1;
                    if(rr_1.to == p_to_1)continue;
#ifdef JEJUDGE
                    judge_1 = 1.0 * p_je_1/rr_1.je1;
                    if(judge_1<MINJE || judge_1>MAXJE) continue;
                    judge_1 = 1.0 * rr_1.je2/q_je_1;
                    if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                    rr_to_1 = rr_1.to;
                    auto res = idsLF[rr_to_1];
                    ans4p_1 -= reslen[rr_to_1];
                    strcpy(ans4p_1, res);
                    res=idsComma[q_to_1];
                    ans4p_1 -= reslen[q_to_1];
                    strcpy(ans4p_1,res);
                    res = idsComma[p_to_1];
                    ans4p_1 -= reslen[p_to_1];
                    strcpy(ans4p_1,res);
                    res =idsComma[i];
                    ans4p_1 -= reslen[i];
                    strcpy(ans4p_1,res);
                    cnt2_1++;
                }
            }
            if(reachable3_1[q_to_1]==i+1){
                visit_1[q_to_1]=1;
                sz_1= path3size_1[q_to_1];
                path3_begin_1 = path3_1[q_to_1];
                path3_end_1 = path3_begin_1+sz_1;
                for(it3_1 = path3_end_1 - 1; it3_1>=path3_begin_1;--it3_1){
                    r_1 = *it3_1;
                    r_to_1 =r_1.to;
                    if(visit_1[r_to_1])continue;
#ifdef JEJUDGE
                    judge_1 = 1.0 * r_1.je/q_je_1;
                    if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                    sz1_1 = path2size_1[r_to_1];
                    path2_begin_1 = path2_1[r_to_1];
                    path2_end_1 = path2_begin_1+sz1_1;
                    for(itr4_1 = path2_end_1-1; itr4_1>=path2_begin_1;--itr4_1){//i->p->q->r-s->i
                        ss_1 = *itr4_1;
                        if(visit_1[ss_1.to])continue;

#ifdef JEJUDGE
                        judge_1 = 1.0 * p_je_1/ss_1.je1;
                        if(judge_1<MINJE || judge_1>MAXJE) continue;
                        judge_1 = 1.0 * ss_1.je2/r_1.je;
                        if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                        ss_to_1 = ss_1.to;
                        auto res=idsLF[ss_to_1];
                        ans5p_1 -= reslen[ss_to_1];
                        strcpy(ans5p_1,res);
                        res=idsComma[r_to_1];
                        ans5p_1 -= reslen[r_to_1];
                        strcpy(ans5p_1,res);
                        res=idsComma[q_to_1];
                        ans5p_1 -= reslen[q_to_1];
                        strcpy(ans5p_1,res);
                        res = idsComma[p_to_1];
                        ans5p_1 -= reslen[p_to_1];
                        strcpy(ans5p_1,res);
                        res =idsComma[i];
                        ans5p_1 -= reslen[i];
                        strcpy(ans5p_1,res);
                        cnt3_1++;
                    }
                }
                visit_1[q_to_1]=0;
            }
            visit_1[q_to_1] = 1;
            n2_1 = outDegrees[q_to_1];
            if(n2_1==0) continue;
            auto gq = G_O1[q_to_1];
            end3_1 = gq + n2_1;
            for (pos3_1=end3_1-1; pos3_1 >= gq; --pos3_1) {

                r_1 = *pos3_1;
                r_to_1 = r_1.to;
                if(r_to_1<=i||visit_1[r_to_1]) continue;
                r_je_1 = r_1.je;
#ifdef JEJUDGE
                judge_1 = 1.0 * r_je_1/q_je_1;
                if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                if(reachable3_1[r_to_1]==i+1){
                    visit_1[r_to_1]=1;
                    sz_1 = path3size_1[r_to_1];
                    path3_begin_1 = path3_1[r_to_1];
                    path3_end_1 = path3_begin_1+sz_1;
                    for(it4_1=path3_end_1-1;it4_1>=path3_begin_1;--it4_1){
                        s_1 = *it4_1;
                        s_to_1 = s_1.to;
                        if(visit_1[s_to_1])continue;
#ifdef JEJUDGE
                        judge_1 = 1.0 * s_1.je/r_je_1;
                        if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                        sz1_1 = path2size_1[s_to_1];
                        path2_begin_1 = path2_1[s_to_1];
                        path2_end_1 = path2_begin_1 + sz1_1;
                        for(itr5_1=path2_end_1-1;itr5_1>=path2_begin_1;itr5_1--){//i->p->q->r-s-t->i
                            tt_1 = *itr5_1;
                            if(visit_1[tt_1.to])continue;
#ifdef JEJUDGE
                            judge_1 = 1.0 * p_je_1/tt_1.je1;
                            if(judge_1<MINJE || judge_1>MAXJE) continue;
                            judge_1 = 1.0 * tt_1.je2/s_1.je;
                            if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                            tt_to_1 = tt_1.to;
                            auto res=idsLF[tt_to_1];
                            ans6p_1 -= reslen[tt_to_1];
                            strcpy(ans6p_1, res);
                            res=idsComma[s_to_1];
                            ans6p_1 -= reslen[s_to_1];
                            strcpy(ans6p_1,res);
                            res=idsComma[r_to_1];
                            ans6p_1 -= reslen[r_to_1];
                            strcpy(ans6p_1,res);
                            res=idsComma[q_to_1];
                            ans6p_1 -= reslen[q_to_1];
                            strcpy(ans6p_1,res);
                            res = idsComma[p_to_1];
                            ans6p_1 -= reslen[p_to_1];
                            strcpy(ans6p_1,res);
                            res =idsComma[i];
                            ans6p_1 -= reslen[i];
                            strcpy(ans6p_1,res);
                            cnt4_1++;
                        }
                    }
                    visit_1[r_to_1]=0;
                }
                visit_1[r_to_1] = 1;
                n3_1 = outDegrees[r_to_1];
                if(n3_1==0) continue;
                auto gr = G_O1[r_to_1];
                end4_1 = gr + n3_1;
                for (pos4_1=end4_1-1; pos4_1 >= gr; pos4_1--) {
                    s_1 = *pos4_1;
                    s_to_1 = s_1.to;
                    if(s_to_1<=i||visit_1[s_to_1]) continue;
                    s_je_1 = s_1.je;
#ifdef JEJUDGE
                    judge_1 = 1.0 * s_je_1/r_je_1;
                    if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                    if(reachable3_1[s_to_1]==i+1) {

                        visit_1[s_to_1] =1;
                        sz_1 = path3size_1[s_to_1];
                        path3_begin_1 = path3_1[s_to_1];
                        path3_end_1 = path3_begin_1+sz_1;
                        for (it5_1 = path3_end_1-1; it5_1 >= path3_begin_1; --it5_1) {

                            t_1 = *it5_1;
                            t_to_1 = t_1.to;

                            if (visit_1[t_to_1])continue;
                            t_je_1 = t_1.je;
#ifdef JEJUDGE
                            judge_1 = 1.0 * t_je_1/s_je_1;
                            if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                            sz1_1 = path2size_1[t_to_1];
                            path2_begin_1 = path2_1[t_to_1];
                            path2_end_1 = path2_begin_1+sz1_1;
                            for (itr6_1 = path2_end_1-1; itr6_1 >= path2_begin_1; --itr6_1) {//i->p->q->r->s->t->u->i
                                uu_1 = *itr6_1;
                                if (visit_1[uu_1.to])continue;
#ifdef JEJUDGE
                                judge_1 = 1.0 * p_je_1/uu_1.je1;
                                if(judge_1<MINJE || judge_1>MAXJE) continue;
                                judge_1 = 1.0 * uu_1.je2/t_1.je;
                                if(judge_1<MINJE || judge_1>MAXJE) continue;
#endif
                                uu_to_1 = uu_1.to;
                                auto res = idsLF[uu_to_1];
                                ans7p_1 -= reslen[uu_to_1];
                                strcpy(ans7p_1, res);
                                res = idsComma[t_to_1];
                                ans7p_1 -= reslen[t_to_1];
                                strcpy(ans7p_1, res);
                                res = idsComma[s_to_1];
                                ans7p_1 -= reslen[s_to_1];
                                strcpy(ans7p_1, res);
                                res = idsComma[r_to_1];
                                ans7p_1 -= reslen[r_to_1];
                                strcpy(ans7p_1, res);
                                res = idsComma[q_to_1];
                                ans7p_1 -= reslen[q_to_1];
                                strcpy(ans7p_1, res);
                                res = idsComma[p_to_1];
                                ans7p_1 -= reslen[p_to_1];
                                strcpy(ans7p_1, res);
                                res = idsComma[i];
                                ans7p_1 -= reslen[i];
                                strcpy(ans7p_1, res);
                                cnt5_1++;
                            }

                        }
                        visit_1[s_to_1] = 0;
                    }
                }
                visit_1[r_to_1] = 0;
            }
            visit_1[q_to_1] = 0;
        }
        visit_1[p_to_1] = 0;
    }
    visit_1[i] = 0;
}
inline void dfs2(uint32_t i) {
    visit_2[i]=1;
    auto gi = G_O1[i];
    end1_2 = gi + outDegrees[i];
    for (pos1_2 = gi; pos1_2 < end1_2; ++pos1_2) {//i->p
        p_2 = *pos1_2;
        p_to_2 = p_2.to;
        if(p_to_2 <= i || visit_2[p_to_2]) continue;
        p_je_2=p_2.je;
        if( reachable2_2[p_to_2] == i+1 ){//i->p->q->i->p
            sz_2 = path2size_2[p_to_2];
            path2_begin_2 = path2_2[p_to_2];
            path2_end_2 = path2_begin_2 +sz_2;
            for(itr2_2=path2_begin_2;itr2_2<path2_end_2;++itr2_2){
                qq_2 = *itr2_2;
#ifdef JEJUDGE
                judge_2 = 1.0 * p_je_2/qq_2.je1;
                if(judge_2<MINJE || judge_2>MAXJE) continue;
                judge_2 = 1.0 * qq_2.je2/p_je_2;
                if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
                qq_to_2 = qq_2.to;
                auto res =idsComma[i];
                strcpy(ans3p_2,res);
                ans3p_2+=reslen[i];
                res = idsComma[p_to_2];
                strcpy(ans3p_2,res);
                ans3p_2+=reslen[p_to_2];
                res=idsLF[qq_to_2];
                strcpy(ans3p_2,res);
                ans3p_2+=reslen[qq_to_2];
                cnt1_2++;
            }
        }
        visit_2[p_to_2] = 1;
        n1_2 = outDegrees[p_to_2];
        if(n1_2==0) continue;
        auto gp = G_O1[p_to_2];
        end2_2 = gp + n1_2;
        for (pos2_2=gp; pos2_2 < end2_2; ++pos2_2) {
            q_2 = *pos2_2;
            q_to_2 = q_2.to;
            if (q_to_2<=i||visit_2[q_to_2])continue;
            q_je_2 = q_2.je;
#ifdef JEJUDGE
            judge_2 = 1.0 * q_je_2/p_je_2;
            if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
            if(reachable2_2[q_to_2]==i+1){
                sz_2 = path2size_2[q_to_2];
                path2_begin_2 = path2_2[q_to_2];
                path2_end_2 = path2_begin_2+sz_2;
                for(itr3_2 = path2_begin_2; itr3_2<path2_end_2; ++itr3_2){//i->p->q->r->i
                    rr_2 = *itr3_2;
                    if(rr_2.to == p_to_2)continue;
#ifdef JEJUDGE
                    judge_2 = 1.0 * p_je_2/rr_2.je1;
                    if(judge_2<MINJE || judge_2>MAXJE) continue;
                    judge_2 = 1.0 * rr_2.je2/q_je_2;
                    if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
//                        if(c_len2>=MAX4NUM){//超过就增加100万字节
//                            MAX4NUM+=add_len;
//                            ans4 = (char*)realloc(ans4,MAX4NUM);
//                        }
                    rr_to_2 = rr_2.to;
                    auto res =idsComma[i];
                    strcpy(ans4p_2,res);
                    ans4p_2+=reslen[i];
                    res = idsComma[p_to_2];
                    strcpy(ans4p_2,res);
                    ans4p_2+=reslen[p_to_2];
                    res=idsComma[q_to_2];
                    strcpy(ans4p_2,res);
                    ans4p_2+=reslen[q_to_2];
                    res=idsLF[rr_to_2];
                    strcpy(ans4p_2,res);
                    ans4p_2+=reslen[rr_to_2];
                    cnt2_2++;
                }
            }
            if(reachable3_2[q_to_2]==i+1){
                visit_2[q_to_2]=1;
                sz_2= path3size_2[q_to_2];
                path3_begin_2 = path3_2[q_to_2];
                path3_end_2 = path3_begin_2+sz_2;
                for(it3_2 = path3_begin_2; it3_2<path3_end_2;++it3_2){
                    r_2 = *it3_2;
                    r_to_2 =r_2.to;
                    if(visit_2[r_to_2])continue;
#ifdef JEJUDGE
                    judge_2 = 1.0 * r_2.je/q_je_2;
                    if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
                    sz1_2 = path2size_2[r_to_2];
                    path2_begin_2 = path2_2[r_to_2];
                    path2_end_2 = path2_begin_2+sz1_2;
                    for(itr4_2 = path2_begin_2; itr4_2<path2_end_2;++itr4_2){//i->p->q->r-s->i
                        ss_2 = *itr4_2;
                        if(visit_2[ss_2.to])continue;

#ifdef JEJUDGE
                        judge_2 = 1.0 * p_je_2/ss_2.je1;
                        if(judge_2<MINJE || judge_2>MAXJE) continue;
                        judge_2 = 1.0 * ss_2.je2/r_2.je;
                        if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
//                            if(c_len3>=MAX5NUM){//超过就增加100万字节
//                                MAX5NUM+=add_len;
//                                ans5 = (char*)realloc(ans5,MAX5NUM);
//                            }
                        ss_to_2 = ss_2.to;
                        auto res =idsComma[i];
                        strcpy(ans5p_2,res);
                        ans5p_2+=reslen[i];
                        res = idsComma[p_to_2];
                        strcpy(ans5p_2,res);
                        ans5p_2+=reslen[p_to_2];
                        res=idsComma[q_to_2];
                        strcpy(ans5p_2,res);
                        ans5p_2+=reslen[q_to_2];
                        res=idsComma[r_to_2];
                        strcpy(ans5p_2,res);
                        ans5p_2+=reslen[r_to_2];
                        res=idsLF[ss_to_2];
                        strcpy(ans5p_2,res);
                        ans5p_2+=reslen[ss_to_2];
                        cnt3_2++;
                    }
                }
                visit_2[q_to_2]=0;
            }
            visit_2[q_to_2] = 1;
            n2_2 = outDegrees[q_to_2];
            if(n2_2==0) continue;
            auto gq = G_O1[q_to_2];
            end3_2 = gq + n2_2;
            for (pos3_2=gq; pos3_2 < end3_2; ++pos3_2) {

                r_2 = *pos3_2;
                r_to_2 = r_2.to;
                if(r_to_2<=i||visit_2[r_to_2]) continue;
                r_je_2 = r_2.je;
#ifdef JEJUDGE
                judge_2 = 1.0 * r_je_2/q_je_2;
                if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
                if(reachable3_2[r_to_2]==i+1){
                    visit_2[r_to_2]=1;
                    sz_2 = path3size_2[r_to_2];
                    path3_begin_2 = path3_2[r_to_2];
                    path3_end_2 = path3_begin_2+sz_2;
                    for(it4_2=path3_begin_2;it4_2<path3_end_2;++it4_2){
                        s_2 = *it4_2;
                        s_to_2 = s_2.to;
                        if(visit_2[s_to_2])continue;
#ifdef JEJUDGE
                        judge_2 = 1.0 * s_2.je/r_je_2;
                        if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
                        sz1_2 = path2size_2[s_to_2];
                        path2_begin_2 = path2_2[s_to_2];
                        path2_end_2 = path2_begin_2 + sz1_2;
                        for(itr5_2=path2_begin_2;itr5_2<path2_end_2;itr5_2++){//i->p->q->r-s-t->i
                            tt_2 = *itr5_2;
                            if(visit_2[tt_2.to])continue;
#ifdef JEJUDGE
                            judge_2 = 1.0 * p_je_2/tt_2.je1;
                            if(judge_2<MINJE || judge_2>MAXJE) continue;
                            judge_2 = 1.0 * tt_2.je2/s_2.je;
                            if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
                            tt_to_2 = tt_2.to;
                            auto res =idsComma[i];
                            strcpy(ans6p_2,res);
                            ans6p_2+=reslen[i];
                            res = idsComma[p_to_2];
                            strcpy(ans6p_2,res);
                            ans6p_2+=reslen[p_to_2];
                            res=idsComma[q_to_2];
                            strcpy(ans6p_2,res);
                            ans6p_2+=reslen[q_to_2];
                            res=idsComma[r_to_2];
                            strcpy(ans6p_2,res);
                            ans6p_2+=reslen[r_to_2];
                            res=idsComma[s_to_2];
                            strcpy(ans6p_2,res);
                            ans6p_2+=reslen[s_to_2];
                            res=idsLF[tt_to_2];
                            strcpy(ans6p_2,res);
                            ans6p_2+=reslen[tt_to_2];
                            cnt4_2++;
                        }
                    }
                    visit_2[r_to_2]=0;
                }
                visit_2[r_to_2] = 1;
                n3_2 = outDegrees[r_to_2];
                if(n3_2==0) continue;
                auto gr = G_O1[r_to_2];
                end4_2 = gr + n3_2;
                for (pos4_2=gr; pos4_2 < end4_2; pos4_2++) {
                    s_2 = *pos4_2;
                    s_to_2 = s_2.to;
                    if(s_to_2<=i||visit_2[s_to_2]) continue;
                    s_je_2 = s_2.je;
#ifdef JEJUDGE
                    judge_2 = 1.0 * s_je_2/r_je_2;
                    if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
                    if(reachable3_2[s_to_2]==i+1) {

                        visit_2[s_to_2] =1;
                        sz_2 = path3size_2[s_to_2];
                        path3_begin_2 = path3_2[s_to_2];
                        path3_end_2 = path3_begin_2+sz_2;
                        for (it5_2 = path3_begin_2; it5_2 < path3_end_2; ++it5_2) {

                            t_2 = *it5_2;
                            t_to_2 = t_2.to;

                            if (visit_2[t_to_2])continue;
                            t_je_2 = t_2.je;
#ifdef JEJUDGE
                            judge_2 = 1.0 * t_je_2/s_je_2;
                            if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif

                            sz1_2 = path2size_2[t_to_2];
                            path2_begin_2 = path2_2[t_to_2];
                            path2_end_2 = path2_begin_2+sz1_2;
                            for (itr6_2 = path2_begin_2; itr6_2 < path2_end_2; ++itr6_2) {//i->p->q->r->s->t->u->i
                                uu_2 = *itr6_2;
                                if (visit_2[uu_2.to])continue;
#ifdef JEJUDGE
                                judge_2 = 1.0 * p_je_2/uu_2.je1;
                                if(judge_2<MINJE || judge_2>MAXJE) continue;
                                judge_2 = 1.0 * uu_2.je2/t_2.je;
                                if(judge_2<MINJE || judge_2>MAXJE) continue;
#endif
//                                    if(c_len5>=MAX7NUM){//超过就增加100万字节
//                                        MAX7NUM+=add_len;
//                                        ans7 = (char*)realloc(ans7,MAX7NUM);
//                                    }
                                uu_to_2 = uu_2.to;
                                auto res = idsComma[i];
                                strcpy(ans7p_2, res);
                                ans7p_2 += reslen[i];
                                res = idsComma[p_to_2];
                                strcpy(ans7p_2, res);
                                ans7p_2 += reslen[p_to_2];
                                res = idsComma[q_to_2];
                                strcpy(ans7p_2, res);
                                ans7p_2 += reslen[q_to_2];
                                res = idsComma[r_to_2];
                                strcpy(ans7p_2, res);
                                ans7p_2 += reslen[r_to_2];
                                res = idsComma[s_to_2];
                                strcpy(ans7p_2, res);
                                ans7p_2 += reslen[s_to_2];
                                res = idsComma[t_to_2];
                                strcpy(ans7p_2, res);
                                ans7p_2 += reslen[t_to_2];
                                res = idsLF[uu_to_2];
                                strcpy(ans7p_2, res);
                                ans7p_2 += reslen[uu_to_2];
                                cnt5_2++;
                            }

                        }
                        visit_2[s_to_2] = 0;
                    }
                }
                visit_2[r_to_2] = 0;
            }
            visit_2[q_to_2] = 0;
        }
        visit_2[p_to_2] = 0;
    }
    visit_2[i] = 0;
}
inline void dfs3(uint32_t i) {
    visit_3[i]=1;
    auto gi = G_O1[i];
    end1_3 = gi + outDegrees[i];
    for (pos1_3 = end1_3-1; pos1_3 >= gi; --pos1_3) {//i->p
        p_3 = *pos1_3;
        p_to_3 = p_3.to;
        if(p_to_3 <= i || visit_3[p_to_3]) continue;
        p_je_3=p_3.je;
        if( reachable2_3[p_to_3] == i+1 ){//i->p->q->i->p
            sz_3 = path2size_3[p_to_3];
            path2_begin_3 = path2_3[p_to_3];
            path2_end_3 = path2_begin_3 +sz_3;
            for(itr2_3=path2_end_3-1;itr2_3>=path2_begin_3;--itr2_3){
                qq_3 = *itr2_3;
#ifdef JEJUDGE
                judge_3 = 1.0 * p_je_3/qq_3.je1;
                if(judge_3<MINJE || judge_3>MAXJE) continue;
                judge_3 = 1.0 * qq_3.je2/p_je_3;
                if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                qq_to_3 = qq_3.to;
                auto res=idsLF[qq_to_3];
                ans3p_3 -= reslen[qq_to_3];
                strcpy(ans3p_3,res);
                res = idsComma[p_to_3];
                ans3p_3 -= reslen[p_to_3];
                strcpy(ans3p_3, res);
                res =idsComma[i];
                ans3p_3 -= reslen[i];
                strcpy(ans3p_3,res);
                cnt1_3++;
            }
        }
        visit_3[p_to_3] = 1;
        n1_3 = outDegrees[p_to_3];
        if(n1_3==0) continue;
        auto gp = G_O1[p_to_3];
        end2_3 = gp + n1_3;
        for (pos2_3=end2_3-1; pos2_3 >= gp; --pos2_3) {
            q_3 = *pos2_3;
            q_to_3 = q_3.to;
            if (q_to_3<=i||visit_3[q_to_3])continue;
            q_je_3 = q_3.je;
#ifdef JEJUDGE
            judge_3 = 1.0 * q_je_3/p_je_3;
            if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
            if(reachable2_3[q_to_3]==i+1){
                sz_3 = path2size_3[q_to_3];
                path2_begin_3 = path2_3[q_to_3];
                path2_end_3 = path2_begin_3+sz_3;
                for(itr3_3 = path2_end_3-1; itr3_3>=path2_begin_3; --itr3_3){//i->p->q->r->i
                    rr_3 = *itr3_3;
                    if(rr_3.to == p_to_3)continue;
#ifdef JEJUDGE
                    judge_3 = 1.0 * p_je_3/rr_3.je1;
                    if(judge_3<MINJE || judge_3>MAXJE) continue;
                    judge_3 = 1.0 * rr_3.je2/q_je_3;
                    if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                    rr_to_3 = rr_3.to;
                    auto res = idsLF[rr_to_3];
                    ans4p_3 -= reslen[rr_to_3];
                    strcpy(ans4p_3, res);
                    res=idsComma[q_to_3];
                    ans4p_3 -= reslen[q_to_3];
                    strcpy(ans4p_3,res);
                    res = idsComma[p_to_3];
                    ans4p_3 -= reslen[p_to_3];
                    strcpy(ans4p_3,res);
                    res =idsComma[i];
                    ans4p_3 -= reslen[i];
                    strcpy(ans4p_3,res);
                    cnt2_3++;
                }
            }
            if(reachable3_3[q_to_3]==i+1){
                visit_3[q_to_3]=1;
                sz_3= path3size_3[q_to_3];
                path3_begin_3 = path3_3[q_to_3];
                path3_end_3 = path3_begin_3+sz_3;
                for(it3_3 = path3_end_3 - 1; it3_3>=path3_begin_3;--it3_3){
                    r_3 = *it3_3;
                    r_to_3 =r_3.to;
                    if(visit_3[r_to_3])continue;
#ifdef JEJUDGE
                    judge_3 = 1.0 * r_3.je/q_je_3;
                    if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                    sz1_3 = path2size_3[r_to_3];
                    path2_begin_3 = path2_3[r_to_3];
                    path2_end_3 = path2_begin_3+sz1_3;
                    for(itr4_3 = path2_end_3-1; itr4_3>=path2_begin_3;--itr4_3){//i->p->q->r-s->i
                        ss_3 = *itr4_3;
                        if(visit_3[ss_3.to])continue;

#ifdef JEJUDGE
                        judge_3 = 1.0 * p_je_3/ss_3.je1;
                        if(judge_3<MINJE || judge_3>MAXJE) continue;
                        judge_3 = 1.0 * ss_3.je2/r_3.je;
                        if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                        ss_to_3 = ss_3.to;
                        auto res=idsLF[ss_to_3];
                        ans5p_3 -= reslen[ss_to_3];
                        strcpy(ans5p_3,res);
                        res=idsComma[r_to_3];
                        ans5p_3 -= reslen[r_to_3];
                        strcpy(ans5p_3,res);
                        res=idsComma[q_to_3];
                        ans5p_3 -= reslen[q_to_3];
                        strcpy(ans5p_3,res);
                        res = idsComma[p_to_3];
                        ans5p_3 -= reslen[p_to_3];
                        strcpy(ans5p_3,res);
                        res =idsComma[i];
                        ans5p_3 -= reslen[i];
                        strcpy(ans5p_3,res);
                        cnt3_3++;
                    }
                }
                visit_3[q_to_3]=0;
            }
            visit_3[q_to_3] = 1;
            n2_3 = outDegrees[q_to_3];
            if(n2_3==0) continue;
            auto gq = G_O1[q_to_3];
            end3_3 = gq + n2_3;
            for (pos3_3=end3_3-1; pos3_3 >= gq; --pos3_3) {

                r_3 = *pos3_3;
                r_to_3 = r_3.to;
                if(r_to_3<=i||visit_3[r_to_3]) continue;
                r_je_3 = r_3.je;
#ifdef JEJUDGE
                judge_3 = 1.0 * r_je_3/q_je_3;
                if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                if(reachable3_3[r_to_3]==i+1){
                    visit_3[r_to_3]=1;
                    sz_3 = path3size_3[r_to_3];
                    path3_begin_3 = path3_3[r_to_3];
                    path3_end_3 = path3_begin_3+sz_3;
                    for(it4_3=path3_end_3-1;it4_3>=path3_begin_3;--it4_3){
                        s_3 = *it4_3;
                        s_to_3 = s_3.to;
                        if(visit_3[s_to_3])continue;
#ifdef JEJUDGE
                        judge_3 = 1.0 * s_3.je/r_je_3;
                        if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                        sz1_3 = path2size_3[s_to_3];
                        path2_begin_3 = path2_3[s_to_3];
                        path2_end_3 = path2_begin_3 + sz1_3;
                        for(itr5_3=path2_end_3-1;itr5_3>=path2_begin_3;itr5_3--){//i->p->q->r-s-t->i
                            tt_3 = *itr5_3;
                            if(visit_3[tt_3.to])continue;
#ifdef JEJUDGE
                            judge_3 = 1.0 * p_je_3/tt_3.je1;
                            if(judge_3<MINJE || judge_3>MAXJE) continue;
                            judge_3 = 1.0 * tt_3.je2/s_3.je;
                            if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                            tt_to_3 = tt_3.to;
                            auto res=idsLF[tt_to_3];
                            ans6p_3 -= reslen[tt_to_3];
                            strcpy(ans6p_3, res);
                            res=idsComma[s_to_3];
                            ans6p_3 -= reslen[s_to_3];
                            strcpy(ans6p_3,res);
                            res=idsComma[r_to_3];
                            ans6p_3 -= reslen[r_to_3];
                            strcpy(ans6p_3,res);
                            res=idsComma[q_to_3];
                            ans6p_3 -= reslen[q_to_3];
                            strcpy(ans6p_3,res);
                            res = idsComma[p_to_3];
                            ans6p_3 -= reslen[p_to_3];
                            strcpy(ans6p_3,res);
                            res =idsComma[i];
                            ans6p_3 -= reslen[i];
                            strcpy(ans6p_3,res);
                            cnt4_3++;
                        }
                    }
                    visit_3[r_to_3]=0;
                }
                visit_3[r_to_3] = 1;
                n3_3 = outDegrees[r_to_3];
                if(n3_3==0) continue;
                auto gr = G_O1[r_to_3];
                end4_3 = gr + n3_3;
                for (pos4_3=end4_3-1; pos4_3 >= gr; pos4_3--) {
                    s_3 = *pos4_3;
                    s_to_3 = s_3.to;
                    if(s_to_3<=i||visit_3[s_to_3]) continue;
                    s_je_3 = s_3.je;
#ifdef JEJUDGE
                    judge_3 = 1.0 * s_je_3/r_je_3;
                    if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                    if(reachable3_3[s_to_3]==i+1) {

                        visit_3[s_to_3] =1;
                        sz_3 = path3size_3[s_to_3];
                        path3_begin_3 = path3_3[s_to_3];
                        path3_end_3 = path3_begin_3+sz_3;
                        for (it5_3 = path3_end_3-1; it5_3 >= path3_begin_3; --it5_3) {

                            t_3 = *it5_3;
                            t_to_3 = t_3.to;

                            if (visit_3[t_to_3])continue;
                            t_je_3 = t_3.je;
#ifdef JEJUDGE
                            judge_3 = 1.0 * t_je_3/s_je_3;
                            if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                            sz1_3 = path2size_3[t_to_3];
                            path2_begin_3 = path2_3[t_to_3];
                            path2_end_3 = path2_begin_3+sz1_3;
                            for (itr6_3 = path2_end_3-1; itr6_3 >= path2_begin_3; --itr6_3) {//i->p->q->r->s->t->u->i
                                uu_3 = *itr6_3;
                                if (visit_3[uu_3.to])continue;
#ifdef JEJUDGE
                                judge_3 = 1.0 * p_je_3/uu_3.je1;
                                if(judge_3<MINJE || judge_3>MAXJE) continue;
                                judge_3 = 1.0 * uu_3.je2/t_3.je;
                                if(judge_3<MINJE || judge_3>MAXJE) continue;
#endif
                                uu_to_3 = uu_3.to;
                                auto res = idsLF[uu_to_3];
                                ans7p_3 -= reslen[uu_to_3];
                                strcpy(ans7p_3, res);
                                res = idsComma[t_to_3];
                                ans7p_3 -= reslen[t_to_3];
                                strcpy(ans7p_3, res);
                                res = idsComma[s_to_3];
                                ans7p_3 -= reslen[s_to_3];
                                strcpy(ans7p_3, res);
                                res = idsComma[r_to_3];
                                ans7p_3 -= reslen[r_to_3];
                                strcpy(ans7p_3, res);
                                res = idsComma[q_to_3];
                                ans7p_3 -= reslen[q_to_3];
                                strcpy(ans7p_3, res);
                                res = idsComma[p_to_3];
                                ans7p_3 -= reslen[p_to_3];
                                strcpy(ans7p_3, res);
                                res = idsComma[i];
                                ans7p_3 -= reslen[i];
                                strcpy(ans7p_3, res);
                                cnt5_3++;
                            }

                        }
                        visit_3[s_to_3] = 0;
                    }
                }
                visit_3[r_to_3] = 0;
            }
            visit_3[q_to_3] = 0;
        }
        visit_3[p_to_3] = 0;
    }
    visit_3[i] = 0;
}
void solve() {
    ans3p = ans3;
    ans4p = ans4;
    ans5p = ans5;
    ans6p = ans6;
    ans7p = ans7;
    visit = (uint32_t *) malloc(nodecnt * sizeof(uint32_t));
    memset(visit, 0, sizeof(uint32_t) * nodecnt);
    nodeReLayer3 = (uint32_t *) malloc(200000 * sizeof(uint32_t));
    uint32_t n1t, n2t, n3t;
    Node k{}, j{}, tt1{};
    uint32_t j1;
    Node *a, *b, *c;
    Node *end1t, *end2t, *end3t;
    uint32_t *psz3, *psz2;
    Node **path3P;
    Node1 **path2P;
    bool flag_m = false;
    while (true) {
        pthread_mutex_lock(&mutex1_2);
        if (e1 - s1 <= 1)flag_m = true;
        s1++;
        pthread_mutex_unlock(&mutex1_2);
        if (flag_m)break;
        uint32_t i = s1;
        if (!outDegrees[i] || !inDegrees[i]) continue;
        auto &gi = G_I1[i];
        n1t = inDegrees[i];
        end1t = n1t + gi;
        int layer3 = 0;
        for (a = gi; a < end1t; a++) {
            k = *a;
            k_to = k.to;
            if (k_to <= i) continue;
            auto &gk = G_I1[k_to];
            n2t = inDegrees[k_to];
            if (n2t == 0) continue;
            end2t = n2t + gk;
            for (b = gk; b < end2t; b++) {//j->k->i
                j = *b;
                j_to = j.to;
                if (j_to < i) continue;
#ifdef JEJUDGE_REVERSE
                judge = 1.0 * k.je / j.je;
                if (judge < MINJE || judge > MAXJE) continue;
#endif
                flag = &reachable2[j_to];
                flag1 = *flag;
                if (flag1 != i + 1) {
                    if (!flag1) {
                        path2[j_to] = (Node1 *) malloc(128 * sizeof(Node1));
                    }
                    *flag = i + 1;
                    path2size[j_to] = 0;
                    nodeReLayer3[layer3++] = j_to;
                }
                psz2 = &path2size[j_to];
                path2P = &path2[j_to];
                switch ((*psz2 + 1) & 127) {//除以128
                    case 0: {
                        *path2P = (Node1 *) realloc(*path2P, (*psz2 + 128) * sizeof(Node1));
                        break;
                    }
                }
                nd1.set(k_to, k.je, j.je);
                (*path2P)[*psz2] = nd1;
                (*psz2)++;
            }
        }
        sort(nodeReLayer3, nodeReLayer3 + layer3);
        for (int cn = 0; cn < layer3; cn++) {//tt->j->k->i
            j1 = nodeReLayer3[cn];
            auto &gj = G_I1[j1];
            n3t = inDegrees[j1];
            if (n3t == 0)continue;
            end3t = n3t + gj;
            for (c = gj; c < end3t; c++) {
                tt1 = *c;
                tt_to = tt1.to;
                if (tt_to <= i)continue;
                flag = &reachable3[tt_to];
                flag1 = *flag;
                if (flag1 != i + 1)//tt->j->k->i
                {
                    if (!flag1) {
                        path3[tt_to] = (Node *) malloc(128 * sizeof(Node));
                    }
                    *flag = i + 1;
                    path3size[tt_to] = 0;
                }
                nd.set(j1, tt1.je);
                psz3 = &path3size[tt_to];
                path3P = &path3[tt_to];
                switch ((*psz3 + 1) & 127) {
                    case 0: {
                        *path3P = (Node *) realloc(*path3P, (*psz3 + 128) * sizeof(Node));
                        break;
                    }
                }
                (*path3P)[*psz3] = nd;
                (*psz3)++;
            }

        }
        dfs(i);
    }
}
void solve_1() {
    ans3_1[MAX_SIZE_3 - 1] = '\0';
    ans4_1[MAX_SIZE_4 - 1] = '\0';
    ans5_1[MAX_SIZE_5 - 1] = '\0';
    ans6_1[MAX_SIZE_6 - 1] = '\0';
    ans7_1[MAX_SIZE_7 - 1] = '\0';
    ans3p_1 = ans3_1 + MAX_SIZE_3 - 1;
    ans4p_1 = ans4_1 + MAX_SIZE_4 - 1;
    ans5p_1 = ans5_1 + MAX_SIZE_5 - 1;
    ans6p_1 = ans6_1 + MAX_SIZE_6 - 1;
    ans7p_1 = ans7_1 + MAX_SIZE_7 - 1;
    visit_1 = (uint32_t *) malloc(nodecnt * sizeof(uint32_t));
    memset(visit_1, 0, sizeof(uint32_t) * nodecnt);
    nodeReLayer3_1 = (uint32_t *) malloc(200000 * sizeof(uint32_t));
    uint32_t n1t, n2t, n3t;
    Node k{}, j{}, tt1{};
    uint32_t j1;
    Node *a, *b, *c;
    Node *end1t, *end2t, *end3t;
    uint32_t *psz3, *psz2;
    Node **path3P;
    Node1 **path2P;
    bool flag_m = false;
    while (true) {
        pthread_mutex_lock(&mutex1_2);
        if (e1 - s1 <= 1)flag_m = true;
        e1--;
        pthread_mutex_unlock(&mutex1_2);
        if (flag_m)break;
        uint32_t i = e1;
        if (!outDegrees[i] || !inDegrees[i]) continue;
        auto &gi = G_I1[i];
        n1t = inDegrees[i];
        end1t = n1t + gi;
        int layer3 = 0;
        for (a = gi; a < end1t; a++) {
            k = *a;
            k_to_1 = k.to;
            if (k_to_1 <= i) continue;
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
                flag_1 = &reachable2_1[j_to_1];
                flag1_1 = *flag_1;
                if (flag1_1 != i + 1) {
                    if (!flag1_1) {
                        path2_1[j_to_1] = (Node1 *) malloc(128 * sizeof(Node1));
                    }
                    *flag_1 = i + 1;
                    path2size_1[j_to_1] = 0;
                    nodeReLayer3_1[layer3++] = j_to_1;
                }
                psz2 = &path2size_1[j_to_1];
                path2P = &path2_1[j_to_1];
                switch ((*psz2 + 1) & 127) {//除以128
                    case 0: {
                        *path2P = (Node1 *) realloc(*path2P, (*psz2 + 128) * sizeof(Node1));
                        break;
                    }
                }
                nd1_1.set(k_to_1, k.je, j.je);
                (*path2P)[*psz2] = nd1_1;
                (*psz2)++;
            }
        }
        sort(nodeReLayer3_1, nodeReLayer3_1 + layer3);
        for (int cn = 0; cn < layer3; cn++) {//tt->j->k->i
            j1 = nodeReLayer3_1[cn];
            auto &gj = G_I1[j1];
            n3t = inDegrees[j1];
            if (n3t == 0)continue;
            end3t = n3t + gj;
            for (c = gj; c < end3t; c++) {
                tt1 = *c;
                tt_to_1 = tt1.to;
                if (tt_to_1 <= i)continue;
                flag_1 = &reachable3_1[tt_to_1];
                flag1_1 = *flag_1;
                if (flag1_1 != i + 1)//tt->j->k->i
                {
                    if (!flag1_1) {
                        path3_1[tt_to_1] = (Node *) malloc (128 * sizeof(Node));
                    }
                    *flag_1 = i + 1;
                    path3size_1[tt_to_1] = 0;
                }
                nd_1.set(j1, tt1.je);
                psz3 = &path3size_1[tt_to_1];
                path3P = &path3_1[tt_to_1];
                switch ((*psz3 + 1) & 127) {
                    case 0: {
                        *path3P = (Node *) realloc(*path3P, (*psz3 + 128) * sizeof(Node));
                        break;
                    }
                }
                (*path3P)[*psz3] = nd_1;
                (*psz3)++;
            }
        }
        dfs1(i);
    }
}
void solve_2() {
    ans3p_2 = ans3_2;
    ans4p_2 = ans4_2;
    ans5p_2 = ans5_2;
    ans6p_2 = ans6_2;
    ans7p_2 = ans7_2;
    visit_2 = (uint32_t *) malloc(nodecnt * sizeof(uint32_t));
    memset(visit_2, 0, sizeof(uint32_t) * nodecnt);
    nodeReLayer3_2 = (uint32_t *) malloc(200000 * sizeof(uint32_t));
    uint32_t n1t, n2t, n3t;
    Node k{}, j{}, tt1{};
    uint32_t j1;
    Node *a, *b, *c;
    Node *end1t, *end2t, *end3t;
    uint32_t *psz3, *psz2;
    Node **path3P;
    Node1 **path2P;
    bool flag_m = false;
    while (true) {
        pthread_mutex_lock(&mutex3_4);
        if (e2 - s2 <= 1)flag_m = true;
        s2++;
        pthread_mutex_unlock(&mutex3_4);
        if (flag_m)break;
        uint32_t i = s2;
        if (!outDegrees[i] || !inDegrees[i]) continue;
        auto &gi = G_I1[i];
        n1t = inDegrees[i];
        end1t = n1t + gi;
        int layer3 = 0;
        for (a = gi; a < end1t; a++) {
            k = *a;
            k_to_2 = k.to;
            if (k_to_2 <= i) continue;
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
                flag_2 = &reachable2_2[j_to_2];
                flag1_2 = *flag_2;
                if (flag1_2 != i + 1) {
                    if (!flag1_2) {
                        path2_2[j_to_2] = (Node1 *) malloc(128 * sizeof(Node1));
                    }
                    *flag_2 = i + 1;
                    path2size_2[j_to_2] = 0;
                    nodeReLayer3_2[layer3++] = j_to_2;
                }
                psz2 = &path2size_2[j_to_2];
                path2P = &path2_2[j_to_2];
                switch ((*psz2 + 1) & 127) {//除以128
                    case 0: {
                        *path2P = (Node1 *) realloc(*path2P, (*psz2 + 128) * sizeof(Node1));
                        break;
                    }
                }
                nd1_2.set(k_to_2, k.je, j.je);
                (*path2P)[*psz2] = nd1_2;
                (*psz2)++;
            }
        }
        sort(nodeReLayer3_2, nodeReLayer3_2 + layer3);
        for (int cn = 0; cn < layer3; cn++) {//tt->j->k->i
            j1 = nodeReLayer3_2[cn];
            auto &gj = G_I1[j1];
            n3t = inDegrees[j1];
            if (n3t == 0)continue;
            end3t = n3t + gj;
            for (c = gj; c < end3t; c++) {
                tt1 = *c;
                tt_to_2 = tt1.to;
                if (tt_to_2 <= i)continue;
                flag_2 = &reachable3_2[tt_to_2];
                flag1_2 = *flag_2;
                if (flag1_2 != i + 1)//tt->j->k->i
                {
                    if (!flag1_2) {
                        path3_2[tt_to_2] = (Node *) malloc (128 * sizeof(Node));
                    }
                    *flag_2 = i + 1;
                    path3size_2[tt_to_2] = 0;
                }
                nd_2.set(j1, tt1.je);
                psz3 = &path3size_2[tt_to_2];
                path3P = &path3_2[tt_to_2];
                switch ((*psz3 + 1) & 127) {
                    case 0: {
                        *path3P = (Node *) realloc(*path3P, (*psz3 + 128) * sizeof(Node));
                        break;
                    }
                }
                (*path3P)[*psz3] = nd_2;
                (*psz3)++;
            }
        }
        dfs2(i);
    }
}
void solve_3() {
    ans3_3[MAX_SIZE_3 - 1] = '\0';
    ans4_3[MAX_SIZE_4 - 1] = '\0';
    ans5_3[MAX_SIZE_5 - 1] = '\0';
    ans6_3[MAX_SIZE_6 - 1] = '\0';
    ans7_3[MAX_SIZE_7 - 1] = '\0';
    ans3p_3 = ans3_3 + MAX_SIZE_3 - 1;
    ans4p_3 = ans4_3 + MAX_SIZE_4 - 1;
    ans5p_3 = ans5_3 + MAX_SIZE_5 - 1;
    ans6p_3 = ans6_3 + MAX_SIZE_6 - 1;
    ans7p_3 = ans7_3 + MAX_SIZE_7 - 1;
    visit_3 = (uint32_t *) malloc(nodecnt * sizeof(uint32_t));
    memset(visit_3, 0, sizeof(uint32_t) * nodecnt);
    nodeReLayer3_3 = (uint32_t *) malloc(200000 * sizeof(uint32_t));
    uint32_t n1t, n2t, n3t;
    Node k{}, j{}, tt1{};
    uint32_t j1;
    Node *a, *b, *c;
    Node *end1t, *end2t, *end3t;
    uint32_t *psz3, *psz2;
    Node **path3P;
    Node1 **path2P;
    bool flag_m = false;
    while (true) {
        pthread_mutex_lock(&mutex3_4);
        if (e2 - s2 <= 1)flag_m = true;
        e2--;
        pthread_mutex_unlock(&mutex3_4);
        if (flag_m)break;
        uint32_t i = e2;
        if (!outDegrees[i] || !inDegrees[i]) continue;
        auto &gi = G_I1[i];
        n1t = inDegrees[i];
        end1t = n1t + gi;
        int layer3 = 0;
        for (a = gi; a < end1t; a++) {
            k = *a;
            k_to_3 = k.to;
            if (k_to_3 <= i) continue;
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
                flag_3 = &reachable2_3[j_to_3];
                flag1_3 = *flag_3;
                if (flag1_3 != i + 1) {
                    if (!flag1_3) {
                        path2_3[j_to_3] = (Node1 *) malloc(128 * sizeof(Node1));
                    }
                    *flag_3 = i + 1;
                    path2size_3[j_to_3] = 0;
                    nodeReLayer3_3[layer3++] = j_to_3;
                }
                psz2 = &path2size_3[j_to_3];
                path2P = &path2_3[j_to_3];
                switch ((*psz2 + 1) & 127) {//除以128
                    case 0: {
                        *path2P = (Node1 *) realloc(*path2P, (*psz2 + 128) * sizeof(Node1));
                        break;
                    }
                }
                nd1_3.set(k_to_3, k.je, j.je);
                (*path2P)[*psz2] = nd1_3;
                (*psz2)++;
            }
        }
        sort(nodeReLayer3_3, nodeReLayer3_3 + layer3);
        for (int cn = 0; cn < layer3; cn++) {//tt->j->k->i
            j1 = nodeReLayer3_3[cn];
            auto &gj = G_I1[j1];
            n3t = inDegrees[j1];
            if (n3t == 0)continue;
            end3t = n3t + gj;
            for (c = gj; c < end3t; c++) {
                tt1 = *c;
                tt_to_3 = tt1.to;
                if (tt_to_3 <= i)continue;
                flag_3 = &reachable3_3[tt_to_3];
                flag1_3 = *flag_3;
                if (flag1_3 != i + 1)//tt->j->k->i
                {
                    if (!flag1_3) {
                        path3_3[tt_to_3] = (Node *) malloc (128 * sizeof(Node));
                    }
                    *flag_3 = i + 1;
                    path3size_3[tt_to_3] = 0;
                }
                nd_3.set(j1, tt1.je);
                psz3 = &path3size_3[tt_to_3];
                path3P = &path3_3[tt_to_3];
                switch ((*psz3 + 1) & 127) {
                    case 0: {
                        *path3P = (Node *) realloc(*path3P, (*psz3 + 128) * sizeof(Node));
                        break;
                    }
                }
                (*path3P)[*psz3] = nd_3;
                (*psz3)++;
            }
        }
        dfs3(i);
    }
}
void save_fwrite_buf(const string &outputFile){
    int ansCnt_=0;
    ansCnt_+=cnt1;
    ansCnt_+=cnt2;
    ansCnt_+=cnt3;
    ansCnt_+=cnt4;
    ansCnt_+=cnt5;

    ansCnt_+=cnt1_1;
    ansCnt_+=cnt2_1;
    ansCnt_+=cnt3_1;
    ansCnt_+=cnt4_1;
    ansCnt_+=cnt5_1;

    ansCnt_+=cnt1_2;
    ansCnt_+=cnt2_2;
    ansCnt_+=cnt3_2;
    ansCnt_+=cnt4_2;
    ansCnt_+=cnt5_2;

    ansCnt_+=cnt1_3;
    ansCnt_+=cnt2_3;
    ansCnt_+=cnt3_3;
    ansCnt_+=cnt4_3;
    ansCnt_+=cnt5_3;

    c_len1 = ans3p - ans3;
    c_len2 = ans4p - ans4;
    c_len3 = ans5p - ans5;
    c_len4 = ans6p - ans6;
    c_len5 = ans7p - ans7;

    c_len1_1 = ans3_1 + MAX_SIZE_3 - ans3p_1 - 1;
    c_len2_1 = ans4_1 + MAX_SIZE_4 - ans4p_1 - 1;
    c_len3_1 = ans5_1 + MAX_SIZE_5 - ans5p_1 - 1;
    c_len4_1 = ans6_1 + MAX_SIZE_6 - ans6p_1 - 1;
    c_len5_1 = ans7_1 + MAX_SIZE_7 - ans7p_1 - 1;

    c_len1_2 = ans3p_2 - ans3_2;
    c_len2_2 = ans4p_2 - ans4_2;
    c_len3_2 = ans5p_2 - ans5_2;
    c_len4_2 = ans6p_2 - ans6_2;
    c_len5_2 = ans7p_2 - ans7_2;

    c_len1_3 = ans3_3 + MAX_SIZE_3 - ans3p_3 - 1;
    c_len2_3 = ans4_3 + MAX_SIZE_4 - ans4p_3 - 1;
    c_len3_3 = ans5_3 + MAX_SIZE_5 - ans5p_3 - 1;
    c_len4_3 = ans6_3 + MAX_SIZE_6 - ans6p_3 - 1;
    c_len5_3 = ans7_3 + MAX_SIZE_7 - ans7p_3 - 1;

    ans3[c_len1] = '\0';
    ans4[c_len2] = '\0';
    ans5[c_len3] = '\0';
    ans6[c_len4] = '\0';
    ans7[c_len5] = '\0';

    ans3_2[c_len1_2] = '\0';
    ans4_2[c_len2_2] = '\0';
    ans5_2[c_len3_2] = '\0';
    ans6_2[c_len4_2] = '\0';
    ans7_2[c_len5_2] = '\0';

#ifdef TEST
    auto ts=clock();
#endif
    /**开始写**/
    FILE *fp = fopen(outputFile.c_str(), "wb");
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
    const char * test_file = "test_data_rm.txt";
    string outputFile = "result.txt";
//    const char * test_file= "/data/test_data.txt";
//    string outputFile = "/projects/student/result.txt";
    Input_Graph(test_file);
    parseInput();
#ifdef TEST
    cout<<"Read+Parse Time: "<<(clock()-ts)/CLOCKS_PER_SEC<<"s"<<endl;
#endif
    topoSort();
    /**多线程共享区间配置**/
    /** 线程1和2共享区间[start1_2, end1_2]*/
    s1 = -1;
    e1 = (int)(nodecnt * 0.18);
    /** 线程3和4共享区间[start3_4, end3_4]*/
    s2 = e1 - 1;
    e2 = nodecnt;
    /**开始多线程**/
    thread threads[THREAD_NUM];
    threads[0] = thread(solve);
    threads[1] = thread(solve_1);
    threads[2] = thread(solve_2);
    threads[3] = thread(solve_3);
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


