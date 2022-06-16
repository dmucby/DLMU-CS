clc;clear
yp = zeros(1,6);
yq = zeros(1,6);
yx = zeros(1,6);
yx(1) = 1;
h = 0.1;
x = [0:0.1:0.5];
n = 6;

for i = 1 : n
    yp(i) = yx(i) + h * fun( x(i) , yx(i));
    yq(i) = yx(i) + h * fun( x(i) , yp(i));
    yx(i+1) = ( yp(i) + yq(i) ) / 2;
    
    X=['第',num2str(i),'次迭代: yp ',num2str(yp(i)),' yq ',
        num2str(yq(i)), ' yx ',num2str(yx(i+1))];
    disp(X)
    
end

figure(1)
plot(x,yx(1,1:6),'o-')
axis([0.1,0.5,1.1,1.5])
xlabel(' x ')
ylabel(' y ')
title('改进欧拉公式计算');