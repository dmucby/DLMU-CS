clear;clc
load date.mat;
%% 数据初始化
[m,n] = size(date);
date1 = date(:,1); % 日期 (date)
flag1_time = date(:,2); % 升旗时间 (min)
flag2_time = date(:,3); % 降旗时间 (min)
sun_time = zeros(m,1);  %日照时长  (min)
new_date = [8];         % 预测的日期 (date)
new_date_time = zeros(1,1);% 预测的结果 (min)
new_date2 = zeros(1,4);    % 更新后的日期 (min)
new_sun_time2 = zeros(1,4);% 更新后的日落时间 (min)

%% 计算日照时间
for i = 1 : m
    sun_time(i) = flag2_time(i) - flag1_time(i);
end

%% 进行牛顿插值
[martix,new_sun_time] = fun1(date1,sun_time,new_date)
martix2 = [date1,martix]

new_date2 = [date1(1),
             new_date,
             date1(2:end)]; 
new_sun_time2 = [sun_time(1),
                new_sun_time,
                sun_time(2:end)]

%% 绘图
figure(1)
plot(date1,sun_time,'o-');grid on; %添加网格
hold on;
plot(new_date2,new_sun_time2,'o-');grid on; %添加网格
xlabel('日期(date)');
ylabel('日照时长(min)');
title('牛顿插值前后天安门广场某月内日照时长');
legend('插值前','插值后');  %图例
