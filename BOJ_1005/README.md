1) dp + dfs를 이용한 풀이

 -목적지로부터 앞으로 이동하면서 dp 갱신해주면서 이동한다.
 
2) 위상정렬 이용한 풀이
 -바로 실행할 수 있는 node를 처음에 queue에 넣는다.
 
 -queue에서 하나씩 빼서 해당 node에서 다음 node로 가는 경우마다 걸리는 시간을 갱신해준다.(최댓값으로) -> dep[]-- 이후 dep[] == 0 이면 queue에 삽입한다.
 
 -이렇게 하면 모든 node에 대해서 실행하는데 걸리는 시간을 계산한다.
 
 -목적지에 해당하는 걸리는 시간을 출력한다.
 
 
 
 -------
 
 앞에서부터 한 단계씩 앞으로 나아가는 형태는 잘못된 풀이.....