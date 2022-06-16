clc;clear;
load data.mat

%% 数据初始化
[m,n] = size(data);
i = data(1,:)  % 节点
t = data(2,:); % 时刻 (h)
y = data(3,:)  % 排沙量(t)

%% 绘图 观察大致关系
figure(1)
plot(t,y,'b-');
xlabel('时刻(h)');
ylabel('排沙量(t)');
title('排沙量和时刻的关系');

%% 分段绘图
% 由观察知排沙量和时刻并非是线性关系,而是由两线性部分组成
% 因此 将问题分成两部分：增长 + 降低
t1 = 460800;  % 由观察知分段点位前端最高值 记录此时x值
index = find(t == t1);
% 分别画出两段的散点图观察
figure(2)
subplot(1,2,1)
plot(t(1:index),y(1:index),'*');
xlabel('时刻(h)');
ylabel('排沙量(t)');
title('排沙量和时刻的关系');
subplot(1,2,2)
plot(t(index:end),y(index:end),'*');
xlabel('时刻(h)');
ylabel('排沙量(t)');
title('排沙量和时刻的关系');


