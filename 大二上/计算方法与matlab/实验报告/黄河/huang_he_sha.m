clc;clear;
load data.mat
%% 数据预处理
% 根据观测次数 以时间节点为轴
% 建立时刻与观测次数的关系式 t(i) = 3600*(12 * i - 4)
% 由于给出了每次观测的水流量v(i)和含沙量c(i) 计算排沙量y(i)=v(i)*c(i) 
% 由于给出了计算结果 本次实验直接使用预处理训练集

[m,n] = size(data);
i = data(1,:)  % 节点
t = data(2,:); % 时刻 (h)
y = data(3,:)  % 排沙量(t)
new_i =  1:1:24;
new_t = 3600 .* (21 .* new_i - 4);

%% 插值函数 求任意时刻的排沙量
p1 = pchip(t,y,new_t); %分段三次埃尔米特插值
p2 = spline(t,y,new_t); %三次样条插值
plot(t,y,'o',new_t,p1,'r-',new_t,p2,'b-');
legend('样本点','三次埃尔米特插值','三次样条插值','Location','SouthEast') %标注显示在东南方向


%% 利用三次样条插值函数计算总排沙量 解决(1)
t1 = t(1); t2 = t(end);
pp = spline(t,y);
pp2 = fn2fm(pp,'pp');
pp2
T1 = quadl(@(tt)fnval(pp,tt),t1,t2) %% 计算总排沙量

