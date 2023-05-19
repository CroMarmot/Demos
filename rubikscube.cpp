#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<(int)(b);i++)
using namespace std;

using xyz = array<int,3>;

xyz mul(const xyz&p, const array<array<int,3>,3> & matrix){
  xyz res={0,0,0};
  rep(i,0,1) rep(j,0,3) rep(k,0,3) res[j] += p[k] * matrix[k][j];
  return res;
}

// https://en.wikipedia.org/wiki/Rotation_matrix
xyz rotateX(const xyz & p){ return mul(p, {{
    {{1,0,0}},
    {{0,0,-1}},
    {{0,1,0}} }}); }
xyz rotateY(const xyz & p){ return mul(p, {{
    {{0,0,1}},
    {{0,1,0}},
    {{-1,0,0}} }}); }
xyz rotateZ(const xyz & p){ return mul(p, {{
    {{0,-1,0}},
    {{1,0,0}},
    {{0,0,1}} }}); }

void auto_test(){
  assert(rotateX({{ 1,2,3 }}) == xyz({{ 1, 3, -2 }}));
  assert(rotateY({{ 1,2,3 }}) == xyz({{ -3, 2, 1 }}));
  assert(rotateZ({{ 1,2,3 }}) == xyz({{ 2, -1, 3 }}));
}
map<char,int> console;
void pcolor(char c){ printf("\033[%dm%c\033[0m",console[c],c); };

vector< vector<pair<int,int> > >ops;
vector<string> opsstr = {};

//        top
//  left front right back
//        bot
//     z
//     |
//     |
//    / \
//   /   \
//  x     y
// 利用三维空间矩阵旋转，简化手写逻辑
template<class T>
void solve(const array<vector<vector<T> >,6 > init){
  int n = init[0].size();
  assert(n > 1);
  assert(n == 3); // TODO n != 3
  rep(i,0,6){
    assert((int)init[i].size() == n);
    rep(j,0,n) assert((int)init[i][j].size() == n);
  }
  using ijk = array<int,3>;
  vector<ijk> poslist;
  array<vector<vector<int> > ,6> ijk2idx;
  rep(i,0,6){
    ijk2idx[i].resize(n);
    rep(j,0,n) {
      ijk2idx[i][j].resize(n);
      rep(k,0,n) {
        ijk2idx[i][j][k]=poslist.size();
        poslist.push_back({i,j,k});
      }
    }
  }

  { // build transform
    map<xyz,int> xyz2idx;
    auto set_map = [&](int i,int j,int k,const xyz&k1){ xyz2idx[k1]=ijk2idx[i][j][k]; };
    rep(j,0,n) rep(k,0,n) set_map(0,j,k,{-(n-1)+2*j,-(n-1)+2*k,n+1}); // Top: 0
    rep(j,0,n) rep(k,0,n) set_map(1,j,k,{-(n-1)+2*k,-(n+1),(n-1)-2*j}); // Left: 1
    rep(j,0,n) rep(k,0,n) set_map(2,j,k,{+(n+1),-(n-1)+2*k,(n-1)-2*j}); // Front: 2
    rep(j,0,n) rep(k,0,n) set_map(3,j,k,{(n-1)-2*k,+(n+1),(n-1)-2*j}); // Rjght: 3
    rep(j,0,n) rep(k,0,n) set_map(4,j,k,{-(n+1),(n-1)-2*k,(n-1)-2*j}); // Back: 4
    rep(j,0,n) rep(k,0,n) set_map(5,j,k,{(n-1)-2*j,-(n-1)+2*k,-(n+1)}); // Bottom: 5

    auto gen = [&](auto filter,const auto & l) -> vector<pair<int,int> >{
      vector<pair<xyz,xyz> > res = {}; // filtered map
      for(const auto&[key,v]:xyz2idx) if(filter(key)) res.push_back({key,key});
      for(auto op:l) for(auto &p: res) p.second = op(p.second);
      vector<pair<int,int> > idxs;
      for(auto &[from,to]: res) idxs.push_back({xyz2idx[from],xyz2idx[to]});
      return idxs;
    };
    auto add=[&](const string &s,const vector<pair<int,int> >&l){
      opsstr.push_back(s);
      ops.push_back(l);
    };
    // config op
    add("v1 up  ",gen([&](const xyz&p)->bool{return p[1]<=-(n-1);},vector{rotateY}));
    add("v1 180 ",gen([&](const xyz&p)->bool{return p[1]<=-(n-1);},vector{rotateY,rotateY}));
    add("v1 down",gen([&](const xyz&p)->bool{return p[1]<=-(n-1);},vector{rotateY,rotateY,rotateY}));

    add("v3 up  ",gen([&](const xyz&p)->bool{return p[1]>=n-1;},vector{rotateY}));
    add("v3 180 ",gen([&](const xyz&p)->bool{return p[1]>=n-1;},vector{rotateY,rotateY}));
    add("v3 down",gen([&](const xyz&p)->bool{return p[1]>=n-1;},vector{rotateY,rotateY,rotateY}));

    add("r1 left ",gen([&](const xyz&p)->bool{return p[2]>=n-1;},vector{rotateZ}));
    add("r1 180  ",gen([&](const xyz&p)->bool{return p[2]>=n-1;},vector{rotateZ,rotateZ}));
    add("r1 right",gen([&](const xyz&p)->bool{return p[2]>=n-1;},vector{rotateZ,rotateZ,rotateZ}));

    add("r3 left ",gen([&](const xyz&p)->bool{return p[2]<=-(n-1);},vector{rotateZ}));
    add("r3 180  ",gen([&](const xyz&p)->bool{return p[2]<=-(n-1);},vector{rotateZ,rotateZ}));
    add("r3 right",gen([&](const xyz&p)->bool{return p[2]<=-(n-1);},vector{rotateZ,rotateZ,rotateZ}));

    add("m1 clock",gen([&](const xyz&p)->bool{return p[0]>=n-1;},vector{rotateX}));
    add("m1 180  ",gen([&](const xyz&p)->bool{return p[0]>=n-1;},vector{rotateX,rotateX}));
    add("m1 rev  ",gen([&](const xyz&p)->bool{return p[0]>=n-1;},vector{rotateX,rotateX,rotateX}));

    add("m3 clock",gen([&](const xyz&p)->bool{return p[0]<=-(n-1);},vector{rotateX}));
    add("m3 180  ",gen([&](const xyz&p)->bool{return p[0]<=-(n-1);},vector{rotateX,rotateX}));
    add("m3 rev  ",gen([&](const xyz&p)->bool{return p[0]<=-(n-1);},vector{rotateX,rotateX,rotateX}));
  }
  using State = vector<T>;
  State space(poslist.size(),0);
  rep(i,0,6) rep(j,0,n) rep(k,0,n) space[ijk2idx[i][j][k]] = init[i][j][k]; // set color in space

  auto show = [&](const State&mp){
    {
      int i = 0;
      rep(j,0,n) {
        printf("   ");
        rep(k,0,n) pcolor((char)mp[ijk2idx[i][j][k]]); // set color in mp
        printf("\n");
      }
    }
    {
      rep(j,0,n) rep(i,1,5) rep(k,0,n) {
        pcolor((char)mp[ijk2idx[i][j][k]]); // set color in mp
        if(k+1==n and i == 4) printf("\n");
      }
    }
    {
      int i = 5;
      rep(j,0,n) {
        printf("   ");
        rep(k,0,n) pcolor((char)mp[ijk2idx[i][j][k]]); // set color in mp
        printf("\n");
      }
    }
    rep(i,0,4*n) printf("=");
    printf("\n");
  };
  show(space);

  // run op
  auto do_op=[&](State&mp, const vector<pair<int,int> >&p2p ) -> void{
    vector< pair<int, T> > res;
    for(auto &[from,to]:p2p) res.push_back({to, mp[from]});
    for(auto [p,c]: res) mp[p] =c;
  };

  auto curc=[&](const State&mp,const ijk& p){return mp[ijk2idx[p[0]][p[1]][p[2]]];};

  auto finish=[&](const State&mp) -> bool{
    rep(i,0,6) rep(j,0,n) rep(k,0,n) if(curc(mp,{i,j,k})!=curc(mp,{i,0,0}))return false;
    return true;
  };

  auto dfs = [&](const State&mp,auto&checker,int dep, auto&l, auto& self)->bool{
    if(checker(mp)) return true;
    if(dep == 0) return false;
    rep(i,0,ops.size()){
      if(l.size() and i/3 == l.back()/3) continue; // 不要连续转一个
      if(dep >= 6) printf("dep[%d] => %d\n",dep, i);
      auto nextmp = mp;
      do_op(nextmp, ops[i]);
      l.push_back(i);
      bool ok = self(nextmp,checker,dep-1,l, self);
      if(ok) return true;
      l.pop_back();
    }
    return false;
  };
  // Dep 2
  // TODO A-star
  // { // 完成低二层
  //  auto hardCodeChecker=[&](const State&mp) -> bool{
  //    rep(i,1,4+1) rep(j,1,n) rep(k,0,n) if(curc(mp,{i,j,k}) != curc(mp,{i,n-1,0})) return false;
  //    rep(j,0,n) rep(k,0,n) if(curc(mp,{5,j,k}) != curc(mp,{5,0,0})) return false; // 底面一样
  //                                                                                 // TODO n != 3
  //    return true;
  //  };
  //  deque<int> oplist = {};
  //  bool ok = dfs(space, hardCodeChecker, 8, oplist,dfs);
  //  if(ok){
  //    printf("ok\n");
  //    for(auto &i:oplist){
  //      cout<<opsstr[i]<<endl;
  //      do_op(space,ops[i]);
  //      show(space);
  //    }
  //  }
  //  get:
  //  v1 up
  //  m1 rev
  //  v1 down
  //  r1 right
  //  v1 up
  //  r1 left
  //  m1 clock
  //  v1 down
  // }

  // 顶部十字
  // auto hardCodeChecker=[&](const State&mp) -> bool{
  //   rep(i,1,4+1) rep(j,1,n) rep(k,0,n) if(curc(mp,{i,j,k}) != curc(mp,{i,n-1,0})) return false;
  //   rep(j,0,n) rep(k,0,n) if(curc(mp,{5,j,k}) != curc(mp,{5,0,0})) return false; // 底面一样
  //                                                                                // TODO n != 3
  //   return curc(mp,{0,0,1}) == curc(mp,{0,1,1})
  //   and curc(mp,{0,1,0}) == curc(mp,{0,1,1})
  //   and curc(mp,{0,1,2}) == curc(mp,{0,1,1})
  //   and curc(mp,{0,2,1}) == curc(mp,{0,1,1});
  // };
  // deque<int> oplist = {};
  // bool ok = dfs(space, hardCodeChecker, 8, oplist,dfs);
  // if(ok){
  //   printf("ok\n");
  //   for(auto &i:oplist){
  //     cout<<opsstr[i]<<endl;
  //     do_op(space,ops[i]);
  //     show(space);
  //   }
  // }
  // v3 up
  // m3 rev
  // r1 left
  // m3 clock
  // r1 right
  // v3 down

  auto hardCodeChecker=[&](const State&mp) -> bool{
    rep(i,1,4+1) rep(j,1,n) rep(k,0,n) if(curc(mp,{i,j,k}) != curc(mp,{i,n-1,0})) return false;
    rep(j,0,n) rep(k,0,n) if(curc(mp,{5,j,k}) != curc(mp,{5,0,0})) return false; // 底面一样
    if(!(curc(mp,{0,0,1}) == curc(mp,{0,1,1})
    and curc(mp,{0,1,0}) == curc(mp,{0,1,1})
    and curc(mp,{0,1,2}) == curc(mp,{0,1,1})
    and curc(mp,{0,2,1}) == curc(mp,{0,1,1}))) return false;

    return curc(mp,{0,0,2}) == curc(mp,{0,1,1})
    or curc(mp,{0,0,2}) == curc(mp,{0,1,1})
    or curc(mp,{0,2,0}) == curc(mp,{0,1,1})
    or curc(mp,{0,2,2}) == curc(mp,{0,1,1});
  };
  deque<int> oplist = {};
  bool ok = dfs(space, hardCodeChecker, 8, oplist,dfs);
  if(ok){
    printf("ok\n");
    for(auto &i:oplist){
      cout<<opsstr[i]<<endl;
      do_op(space,ops[i]);
      show(space);
    }
  }


}

int main(){
  auto_test();
  // green yellow,orange,blue, white, red
  console['g'] = 32;
  console['y'] = 33;
  console['o'] = 35;
  console['b'] = 34;
  console['w'] = 37;
  console['r'] = 31;
  solve<char>({{
      { // Top
      {'y','o','b'},
      {'o','o','o'},
      {'b','o','w'},
      },{ // Left
      {'o','y','o'},
      {'y','y','y'},
      {'y','y','y'},
      },{ // Front
      {'w','b','o'},
      {'g','g','g'},
      {'g','g','g'},
      },{ // Right
      {'g','g','y'},
      {'w','w','w'},
      {'w','w','w'},
      },{ // back
      {'o','w','g'},
      {'b','b','b'},
      {'b','b','b'},
      },{ // bottom
        {'r','r','r'},
          {'r','r','r'},
          {'r','r','r'},
      }
  }});
  return 0;
}


// 第二层
// { // Top
// {'o','g','b'},
// {'g','o','w'},
// {'y','o','g'},
// },{ // Left
// {'w','y','o'},
// {'y','y','y'},
// {'y','y','y'},
// },{ // Front
// {'b','b','o'},
// {'o','g','g'},
// {'g','g','g'},
// },{ // Right
// {'y','o','o'},
// {'w','w','w'},
// {'w','w','w'},
// },{ // back
// {'w','o','g'},
// {'b','b','b'},
// {'b','b','b'},
// },{ // bottom
//   {'r','r','r'},
//     {'r','r','r'},
//     {'r','r','r'},
// }
//
// v1 up
//    bgb
//    oow
//    gog
// oyyrboyoowoy
// yyyrggwwwbbg
// wyyrggwwwbbo
//    brr
//    brr
//    grr
// ============
// m1 rev
//    bgb
//    oow
//    yww
// oygoggroowoy
// yyobggrwwbbg
// wygrrrbwwbbo
//    yyy
//    brr
//    grr
// ============
// v1 down
//    ogb
//    gow
//    yww
// wyobggroowog
// yyyoggrwwbbb
// gogyrrbwwbby
//    oyy
//    brr
//    rrr
// ============
// r1 right
//    bww
//    gow
//    ogy
// wogwyobggroo
// yyyoggrwwbbb
// gogyrrbwwbby
//    oyy
//    brr
//    rrr
// ============
// v1 up
//    www
//    oow
//    ygy
// gygoyobggroo
// oyobggrwwbbg
// wygrrrbwwbbb
//    yyy
//    brr
//    orr
// ============
// r1 left
//    yow
//    gow
//    yww
// oyobggroogyg
// oyobggrwwbbg
// wygrrrbwwbbb
//    yyy
//    brr
//    orr
// ============
// m1 clock
//    yow
//    gow
//    goo
// oyyrbbyoogyg
// oyyrggwwwbbg
// wyyrggwwwbbb
//    brr
//    brr
//    orr
// ============
// v1 down
//    bow
//    gow
//    goo
// wooybbyoogyo
// yyygggwwwbbb
// yyygggwwwbbb
//    rrr
//    rrr
//    rrr
// ============

// -------------------------------------------------------

// 顶层十字
//      { // Top
//      {'b','o','w'},
//      {'g','o','w'},
//      {'g','o','o'},
//      },{ // Left
//      {'w','o','o'},
//      {'y','y','y'},
//      {'y','y','y'},
//      },{ // Front
//      {'y','b','b'},
//      {'g','g','g'},
//      {'g','g','g'},
//      },{ // Right
//      {'y','o','o'},
//      {'w','w','w'},
//      {'w','w','w'},
//      },{ // back
//      {'g','y','o'},
//      {'b','b','b'},
//      {'b','b','b'},
//      },{ // bottom
//        {'r','r','r'},
//          {'r','r','r'},
//          {'r','r','r'},
//      }
// v3 up
//    bob
//    gog
//    gog
// wooybrwwyoyo
// yyyggrwwowbb
// yyyggrwwowbb
//    rrb
//    rrb
//    rrg
// ============
// m3 rev
//    yoo
//    gog
//    gog
// booybrwwgwwo
// oyyggrwwrbby
// byyggrwwrbbo
//    rrb
//    rrb
//    wyy
// ============
// r1 left
//    ggy
//    ooo
//    ggo
// ybrwwgwwoboo
// oyyggrwwrbby
// byyggrwwrbbo
//    rrb
//    rrb
//    wyy
// ============
// m3 clock
//    boy
//    ooo
//    ggo
// wbrwwgwwgoyo
// yyyggrwwgobb
// yyyggrwwybbb
//    rrb
//    rrb
//    rro
// ============
// r1 right
//    yoo
//    oog
//    bog
// oyowbrwwgwwg
// yyyggrwwgobb
// yyyggrwwybbb
//    rrb
//    rrb
//    rro
// ============
// v3 down
//    yob
//    ooo
//    bow
// oyowboggyowg
// yyygggwwwbbb
// yyygggwwwbbb
//    rrr
//    rrr
//    rrr
// ============


