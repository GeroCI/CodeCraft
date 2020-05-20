//
// Created by Geroci on 2020/4/26.
//
#include<bits/stdc++.h>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
#define INF 0x3fffffff
#define Thread_Num 12
const int MAX_N=280000;
char idsComma[MAX_N][20]; //0...n to sorted id
char idsLF[MAX_N][20]; //0...n to sorted id
uint32_t G_O[MAX_N][50];
uint32_t G_I[MAX_N][50];
uint32_t inDegrees[MAX_N];
uint32_t outDegrees[MAX_N];
uint32_t inDegrees_tmp[MAX_N];
char ans3[Thread_Num][20*1024*1024/2];//3环
char ans4[Thread_Num][20*1024*1024/2];//4环
char ans5[Thread_Num][40*1024*1024/2];//5环
char ans6[Thread_Num][84000000/2];//6环
char ans7[Thread_Num][149000000/2];//7环
int clen1[Thread_Num];
int clen2[Thread_Num];
int clen3[Thread_Num];
int clen4[Thread_Num];
int clen5[Thread_Num];
int cnt[Thread_Num][5];
thread_local bool visit[MAX_N];
thread_local int isValid[MAX_N];
thread_local char *anst1, *anst2, *anst3, *anst4, *anst5;
thread_local int *cn1, *cn2, *cn3, *cn4, *cn5;
int que[MAX_N];
int front=0,rear=0;
uint32_t MINV=INF,MAXV=0;
thread_local int *c_len1, *c_len2, *c_len3, *c_len4, *c_len5;
char buf_path[20];
int idx_1=0,idx_2=0;
thread_local uint32_t *pos1, *pos2, *pos3, *pos4, *pos5, *pos6, *pos7;
thread_local uint32_t *end1, *end2, *end3, *end4, *end5, *end6, *end7;

thread_local int n1, n2, n3, n4, n5, n6;
thread_local uint32_t p, q, r, s, t, u;
//#define TEST
//#define TESTREAD

inline void Input_Graph(const char * &testFile) {
#ifdef TEST_READ
    int tm = clock();
#endif
    uintmax_t icnt = 0;
    size_t length;
    int fd = open(testFile, O_RDONLY);
    // obtain file size
    struct stat sb{};
    fstat(fd, &sb);
    length = sb.st_size;
    const char* addr = static_cast<const char*>(mmap(nullptr, length, PROT_READ, MAP_PRIVATE, fd, 0u));

    auto e = addr + length;
    int c = 0;
    uint32_t tr = 0,ur=0,vr=0;
    for(;addr && addr!=e;addr++) {
        if(*addr=='\n'){
            c=0;
            icnt++;
            continue;
        }
        if(c==2) {
            continue;
        }
        if(*addr==','){
            if(c==0) ur=tr;
            if(c==1) vr=tr;
            if(tr>MAXV) MAXV = tr;
            if(tr<MINV) MINV = tr;
            tr=0;
            c++;
            if(c==2){
                G_O[ur][outDegrees[ur]++]=vr;
                G_I[vr][inDegrees[vr]++]=ur;
            }
            continue;
        }
        tr = tr * 10 + *addr - '0';
    }
    munmap((void *) addr, length);
    close(fd);
#ifdef TEST_READ
    cout<<"Read Time:"<<clock()-tm<<endl;
    cout<<"Records:"<<icnt<<endl;
#endif
}


inline int cmp ( const void *a , const void *b )
{
    return *(int *)a - *(int *)b;
}
inline void EnQue(int start_,int end_){
    for (int i = start_; i <= end_; i += 1) {
        idx_1=sprintf(buf_path,"%d",i);
        idx_2=idx_1;
        buf_path[idx_1++]=',';
        buf_path[idx_1]='\0';
        strcpy(idsComma[i],buf_path);
        buf_path[idx_2++]='\n';
        buf_path[idx_2]='\0';
        strcpy(idsLF[i],buf_path);
        if (0 == inDegrees[i]) {//入队
//            que.push(i);
            que[rear++]=i;
        }
    }
}
inline void Init_Sort(int start_,int end_){
    for (int i = start_; i < end_; i += 1) {
        if (outDegrees[i]>1 && inDegrees[i]>0) {//排序
            qsort(G_O[i],outDegrees[i],sizeof(uint32_t),cmp);
        }
        if(inDegrees_tmp[i]>1 && outDegrees[i]>0){
            qsort(G_I[i],inDegrees_tmp[i],sizeof(uint32_t),cmp);
        }
    }
}
inline void topoSort(){
    memcpy(inDegrees_tmp,inDegrees,280000*sizeof(uint32_t));
    std::thread thds[Thread_Num];
    uint32_t tmp;
    EnQue(MINV,MAXV);
    while(front!=rear){
        int ut =que[front++];
        auto gu = G_O[ut];
        for(uint32_t i=0;i<outDegrees[ut];i+=1){
            tmp = gu[i];
            if(0==--inDegrees[tmp]){
                que[rear++]=tmp;
            }
        }
        outDegrees[ut]=0;
    }
    uint32_t nodeCnt = MAXV - MINV + 1;
    uint32_t seq_len=nodeCnt/Thread_Num/6;
    thds[0] = std::thread(Init_Sort,0,seq_len);
    thds[1] = std::thread(Init_Sort,seq_len,2*seq_len);
    thds[2] = std::thread(Init_Sort,2*seq_len,3*seq_len);
    thds[3] = std::thread(Init_Sort,3*seq_len,4*seq_len);
    thds[4] = std::thread(Init_Sort,4*seq_len,5*seq_len);
    thds[5] = std::thread(Init_Sort,5*seq_len,6*seq_len);
    thds[6] = std::thread(Init_Sort,6*seq_len,nodeCnt/10);
    thds[7] = std::thread(Init_Sort,nodeCnt/10,nodeCnt/8);
    thds[8] = std::thread(Init_Sort,nodeCnt/8,nodeCnt/6);
    thds[9] = std::thread(Init_Sort,nodeCnt/6,nodeCnt/4);
    thds[10] = std::thread(Init_Sort,nodeCnt/4,nodeCnt/2);
    thds[11] = std::thread(Init_Sort,nodeCnt/2,nodeCnt);
    for(auto & thd : thds){
        thd.join();
    }
}
void dfs(uint32_t &i) {
    auto gi = G_O[i];
    end1 = gi + outDegrees[i];
//    pos1 = lower_bound(gi, end1, i);
    for (pos1=gi; pos1 < end1; pos1++) {//i->p
        p = *pos1;
        if(p<i) continue;
        visit[p] = true;
        n1 = outDegrees[p];
        auto gp = G_O[p];
        end2 = gp + n1;
//        pos2 = upper_bound(gp, end2, i);
        for (pos2=gp; pos2 < end2; pos2++) {//i->p->q
            q = *pos2;
            if(q<=i) continue;
            if (visit[q])continue;
            visit[q] = true;
            n2 = outDegrees[q];
            auto gq = G_O[q];
            end3 = gq + n2;
//            pos3 = lower_bound(gq, end3, i);
            for (pos3=gq; pos3 < end3; pos3++) {//i->p->q->r
                r = *pos3;
                if(r<i) continue;
                if (r == i) {//3环
                    auto res =idsComma[i];
                    strcpy(anst1+*c_len1,res);
                    *c_len1+=strlen(res);
                    res = idsComma[p];
                    strcpy(anst1+*c_len1,res);
                    *c_len1+=strlen(res);
                    res=idsLF[q];
                    strcpy(anst1+*c_len1,res);
                    *c_len1+=strlen(res);
                    (*cn1)++;
                    continue;
                }
                if (visit[r])continue;
                visit[r] = true;
                n3 = outDegrees[r];
                auto gr = G_O[r];
                end4 = gr + n3;
//                pos4 = lower_bound(gr, end4, i);
                for (pos4=gr; pos4 < end4; pos4++) {//i->p->q->r->s
                    s = *pos4;
                    if(s<i) continue;
                    if (s == i) {//4环
                        auto res =idsComma[i];
                        strcpy(anst2+*c_len2,res);
                        *c_len2+=strlen(res);
                        res = idsComma[p];
                        strcpy(anst2+*c_len2,res);
                        *c_len2+=strlen(res);
                        res=idsComma[q];
                        strcpy(anst2+*c_len2,res);
                        *c_len2+=strlen(res);
                        res=idsLF[r];
                        strcpy(anst2+*c_len2,res);
                        *c_len2+=strlen(res);
                        (*cn2)++;
                        continue;
                    }
                    if (visit[s]||isValid[s] != i) continue;
                    visit[s] = true;
                    n4 = outDegrees[s];
                    auto gs = G_O[s];
                    end5 = gs+n4;
//                    pos5 = lower_bound(gs, end5, i);
                    for (pos5=gs; pos5 < end5; pos5++) {//i->p->q->r->s->t
                        t = *pos5;
                        if(t<i) continue;
                        if (t == i) {
                            auto res =idsComma[i];
                            strcpy(anst3+*c_len3,res);
                            *c_len3+=strlen(res);
                            res = idsComma[p];
                            strcpy(anst3+*c_len3,res);
                            *c_len3+=strlen(res);
                            res=idsComma[q];
                            strcpy(anst3+*c_len3,res);
                            *c_len3+=strlen(res);
                            res=idsComma[r];
                            strcpy(anst3+*c_len3,res);
                            *c_len3+=strlen(res);
                            res=idsLF[s];
                            strcpy(anst3+*c_len3,res);
                            *c_len3+=strlen(res);
                            (*cn3)++;
                            continue;
                        }
                        if (visit[t]||isValid[t] != i)
                            continue;
                        visit[t] = true;
                        auto gt = G_O[t];
                        n5 = outDegrees[t];
                        end6 = gt+n5;
//                        pos6 = lower_bound(gt, end6, i);
                        for (pos6=gt; pos6 < end6; pos6++) {
                            u = *pos6;
                            if(u<i) continue;
                            if (u == i) {//i->p->q->r->s->t->u
                                auto res =idsComma[i];
                                strcpy(anst4+*c_len4,res);
                                *c_len4+=strlen(res);
                                res = idsComma[p];
                                strcpy(anst4+*c_len4,res);
                                *c_len4+=strlen(res);
                                res=idsComma[q];
                                strcpy(anst4+*c_len4,res);
                                *c_len4+=strlen(res);
                                res=idsComma[r];
                                strcpy(anst4+*c_len4,res);
                                *c_len4+=strlen(res);
                                res=idsComma[s];
                                strcpy(anst4+*c_len4,res);
                                *c_len4+=strlen(res);
                                res=idsLF[t];
                                strcpy(anst4+*c_len4,res);
                                *c_len4+=strlen(res);
                                (*cn4)++;
                                continue;
                            }
                            if (visit[u] || isValid[u] != i) continue;
                            n6 = outDegrees[u];
                            auto gu = G_O[u];
                            end7 = n6 + gu;
                            pos7 = lower_bound(gu, end7, i);
                            if(pos7==end7 || *pos7!=i) continue;
                            auto res =idsComma[i];
                            strcpy(anst5+*c_len5,res);
                            *c_len5+=strlen(res);
                            res = idsComma[p];
                            strcpy(anst5+*c_len5,res);
                            *c_len5+=strlen(res);
                            res=idsComma[q];
                            strcpy(anst5+*c_len5,res);
                            *c_len5+=strlen(res);
                            res=idsComma[r];
                            strcpy(anst5+*c_len5,res);
                            *c_len5+=strlen(res);
                            res=idsComma[s];
                            strcpy(anst5+*c_len5,res);
                            *c_len5+=strlen(res);
                            res=idsComma[t];
                            strcpy(anst5+*c_len5,res);
                            *c_len5+=strlen(res);
                            res=idsLF[u];
                            strcpy(anst5+*c_len5,res);
                            *c_len5+=strlen(res);
                            (*cn5) ++;
                        }
                        visit[t] = false;
                    }
                    visit[s] = false;
                }
                visit[r] = false;
            }
            visit[q] = false;
        }
        visit[p] = false;
    }
}

void solve(uint32_t start, uint32_t end, int tid){
//    uint32_t n1=0,n2=0,n3=0,k=0,j=0,t=0;
    uint32_t k=0,j=0;
    uint32_t * a, *b, *c;
    anst1 = ans3[tid], anst2 = ans4[tid], anst3 = ans5[tid], anst4 = ans6[tid], anst5 = ans7[tid];
    cn1 = cnt[tid], cn2 = cnt[tid]+1, cn3 = cnt[tid]+2, cn4 = cnt[tid]+3, cn5 = cnt[tid]+4;
    c_len1 = clen1+tid, c_len2 = clen2+tid, c_len3 = clen3+tid, c_len3 = clen3+tid, c_len4 = clen4+tid, c_len5 = clen5+tid;
    //    uint32_t *end1, *end2, *end3;
    for(uint32_t i=start;i<end;i++) {
        if(outDegrees[i]==0||inDegrees[i]==0) continue;
        auto &gi = G_I[i];
        n1=inDegrees_tmp[i];
        end1 = n1+gi;
//        a = lower_bound(gi,end1,i);
        for (a=gi;a<end1;a++) {
            k = *a;
            if(k<i) continue;
            isValid[k]=i;
            auto &gk = G_I[k];
            n2 = inDegrees_tmp[k];
            if (n2 == 0) continue;
            end2 = n2+gk;
//            b = upper_bound(gk,end2,i);
            for (b=gk; b < end2; b++) {//第三
                j = *b;
                if(j<=i) continue;
                isValid[j]=i;
                auto &gj = G_I[j];
                //路径j-k-i
                n3 = inDegrees_tmp[j];
                if(n3==0) continue;
                end3 = n3+gj;
//                c = upper_bound(gj, end3, i);
                for (c=gj; c < end3; c++){
                    t = *c;//t-j-k-i
                    if(t<=i) continue;
                    if(t!=k) {
                        isValid[t]=i;
                    }
                }
            }
        }
        dfs(i);
    }
}
void multi_solve(){
    std::thread thds[Thread_Num];
//    uint32_t nodeCnt = MAXV - MINV + 1;
//    uint32_t seq_len=nodeCnt/(Thread_Num)/2;
//    thds[0] = thread(solve,0,seq_len, 0);
//    thds[1] = thread(solve,seq_len, 2*seq_len, 1);
//    thds[2] = thread(solve,2*seq_len,nodeCnt/2, 2);
//    thds[3] = thread(solve,nodeCnt/2,nodeCnt, 3);
    uint32_t nodeCnt = MAXV - MINV + 1;
    uint32_t seq_len=nodeCnt/Thread_Num/6;
    thds[0] = std::thread(solve,0,seq_len,0);
    thds[1] = std::thread(solve,seq_len,2*seq_len,1);
    thds[2] = std::thread(solve,2*seq_len,3*seq_len,2);
    thds[3] = std::thread(solve,3*seq_len,4*seq_len,3);
    thds[4] = std::thread(solve,4*seq_len,5*seq_len,4);
    thds[5] = std::thread(solve,5*seq_len,6*seq_len,5);
    thds[6] = std::thread(solve,6*seq_len,nodeCnt/10,6);
    thds[7] = std::thread(solve,nodeCnt/10,nodeCnt/8,7);
    thds[8] = std::thread(solve,nodeCnt/8,nodeCnt/6,8);
    thds[9] = std::thread(solve,nodeCnt/6,nodeCnt/4,9);
    thds[10] = std::thread(solve,nodeCnt/4,nodeCnt/2,10);
    thds[11] = std::thread(solve,nodeCnt/2,nodeCnt,11);
    for(auto & thd : thds){
        thd.join();
    }
}

void save_fwrite_buf(const string &outputFile,int &ansCnt_){
    auto tw = clock();
    FILE *fp = fopen(outputFile.c_str(), "wb");
    char buf[1024];
    int idx = sprintf(buf, "%d\n", ansCnt_);
    buf[idx] = '\0';
    fwrite(buf, idx, sizeof(char), fp);
    for (int i = 0; i < 5; i++) {
        for(int tid=0;tid<Thread_Num;tid++) {
            char *pw[5] = {ans3[tid], ans4[tid], ans5[tid], ans6[tid], ans7[tid]};
            int l[5] = {clen1[tid], clen2[tid], clen3[tid], clen4[tid], clen5[tid]};
            fwrite(pw[i], l[i], 1, fp);
        }
    }
    fclose(fp);
    cout<<"write time:"<<clock()-tw<<endl;
}
int main(){
    auto ts=clock();
    const char * test_file = "test_data_1004812.txt";
    string outputFile = "result.txt";
//    const char * test_file= "/data/test_data.txt";
//    string outputFile = "/projects/student/result.txt";
    Input_Graph(test_file);
    topoSort();
    multi_solve();
    int sum=0;
    for(auto & tid : cnt) {
        for (int i : tid) {
            sum += i;
        }
    }
    save_fwrite_buf(outputFile,sum);
    cout<<sum<<endl;
    cout<<"All time:"<<clock()-ts<<endl;
    return 0;
}


