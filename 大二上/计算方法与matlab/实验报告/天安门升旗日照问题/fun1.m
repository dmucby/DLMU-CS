function [A,y]= fun1(X,Y,x)
%   Newton插值函数
%   X为已知数据点的x坐标
%   Y为已知数据点的y坐标
%   x为插值点的x坐标
%   函数返回A差商表
%   y为各插值点函数值

n=length(X); m=length(x);
for t=1:m
    z=x(t); A=zeros(n,n);A(:,1)=Y';
    s1=0.0; y=0.0;
    for  j=2:n
       for i=j:n
           A(i,j)=(A(i,j-1)- A(i-1,j-1))/(X(i)-X(i-j+1));
       end
    end
    for k=1:n
        p=1.0;
        for j=1:k-1
            p=p*(z-X(j));
        end
        s1=s1+A(k,k)*p;        
    end
    s2(t)=s1;
end
    y=s2;
end
