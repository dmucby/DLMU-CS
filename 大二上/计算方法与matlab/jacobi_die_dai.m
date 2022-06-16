clear
clc
n = input('Enter number of equations, n:  ');          %根据提示输入题目要求的n
%  %构造矩阵A
%  for m=n
%     A=zeros(m,m);
%     for m=1:m
%         A(m,m)=20;
%     end
%     for m=2:m
%         A(m,m-1)=-8;
%         A(m-1,m)=-8;
%     end
%     for m=3:m
%         A(m,m-2)=1;
%         A(m-2,m)=1;
%     end
%  end

x = ones(n,1);
b = zeros(n,1);
D = diag(diag(A));                              %求A的对角矩阵
L = tril(A,-1);                                %求A的下三角矩阵
U = triu(A,1);                                 %求A的上三角矩阵
err = 1E-6;
%Jacobil迭代
I=eye(n);										%生成单位矩阵
BJ=I-D\A;     									%生成迭代矩阵BJ
pJ=vrho(BJ);                                    % 矩阵的谱半径
R_j = -log(pJ);                                  %J迭代渐进收敛速度
g=D\b;
jacobilk = 1;                                   %jacobil迭代次数
xJ = ones(n,1);								%初始迭代向量（1，1，1，1,..）T
it_max = 200;                                   %设定上限，万一无限循环
while jacobilk <= it_max
    xjafter=BJ*xJ+g; 
	xJ=xjafter;
    if norm(xJ,inf)<err
            break;
    end
	jacobilk = jacobilk +1;
end 
