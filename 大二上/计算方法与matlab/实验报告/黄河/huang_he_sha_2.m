clc;clear;
load data.mat
load data1.mat

%% 数据初始化
[m,n] = size(data);
i = data(1,:)   % 节点
t = data(2,:);  % 时刻 (h)
y = data(3,:)   % 排沙量(t)
v = data1(1,:); % 水流量(m^3/s)
c = data1(2,:)  % 含沙量(t)

%% 模型求解
% 由散点图知一二段大致成线性关系
% 根据所给值分段建立模型
y = c .* v; % 计算排沙量 
format long e
t1 = 460800;  % 由观察知分段点位前端最高值 记录此时x值
index = find(t == t1);

%% 第一段模型拟合
for j =1:2
    nihe1{j} = polyfit(v(1:index),y(1:index),j); %拟合多项式 系数从高到低
    yhat1{j} = polyval(nihe1{j},v(1:index));     %求预测值
    %以下求误差平方和与剩余标准差
    remse1(j) = sqrt(sum((y(1:index)-yhat1{j}).^2)/(10-j)); % 求剩余标准差
end
nihe1{:}
cha1 = remse1
    
%% 第二阶段拟合
% 以下是第二阶段的拟合
for j =1:3
    nihe2{j} = polyfit(v(index+1:end),y(index+1:end),(j+1)); % 这里使用细胞数组
    yhat2{j} = polyval(nihe2{j},v(index+1:end));
    remse2(j) = sqrt(sum((y(index+1:end)-yhat2{j}).^2)/(11-j)); % 求剩余标准差
end
nihe2{:} % 显示细胞数组的所有元素
cha2 = remse2
format
