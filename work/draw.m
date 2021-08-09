clear;
clc;
load('Data001.mat');
xx = Data001(:,1)';
yy = Data001(:,2)';
%x(1,336) = x(1,1);
%y(1,336) = y(1,1);
%yy = ppval(pp,x);
%plot(x,pp,'r',x,y,'b--');

xx=[xx(333),xx(334),xx(335),xx,xx(1),xx(2)];
yy=[yy(333),yy(334),yy(335),yy,yy(1),yy(2)];
hg=[];

tt = 0;
for i = 2 : 340
    tt(i) = tt(i-1) + sqrt((xx(i)-xx(i-1))^2 + (yy(i)-yy(i-1))^2);
end

for i=4:338
    t=(0:0.001:1);
    ttt = t * (tt(i)-tt(i-1))+tt(i-1);
    %x0=xx(i);x1=xx(i+1);x2=xx(i+2);x3=xx(i+3);
    %y0=yy(i);y1=yy(i+1);y2=yy(i+2);y3=yy(i+3);
    %a0=(x0+4*x1+x2)/6;a1=-(x0-x2)/2;a2=(x0-2*x1+x2)/2;a3=-(x0-3*x1+3*x2-x3)/6;
    %b0=(y0+4*y1+y2)/6;b1=-(y0-y2)/2;b2=(y0-2*y1+y2)/2;b3=-(y0-3*y1+3*y2-y3)/6;
    %x=a0+a1*t+a2*t.^2+a3*t.^3;
    %y=b0+b1*t+b2*t.^2+b3*t.^3;
    %hg=[hg;a0,a1,a2,a3;b0,b1,b2,b3];%hg为x和y拟合的系数，
    %第1，2行分别为第一段x，y的系数，3，4为第二段，类推
    %plot(x,y)
    %hold on
    
    syms x;

    p1(x) = (x-tt(i-1))^3 / ((tt(i+2)-tt(i-1))*(tt(i+1)-tt(i-1))*(tt(i)-tt(i-1)));

    p2(x) = (tt(i+2)-x)*(x-tt(i-1))^2 / ((tt(i+2)-tt(i-1))*(tt(i)-tt(i-1))*(tt(i+1)-tt(i-1))) + ...
            (x-tt(i-2))^2*(tt(i)-x)/((tt(i+1)-tt(i-2))*(tt(i)-tt(i-2))*(tt(i)-tt(i-1))) + (tt(i+1)-x)*(x-tt(i-1))*(x-tt(i-2))/((tt(i+1)-tt(i-1))*(tt(i)-tt(i-1))*(tt(i+1)-tt(i-2)));

    p3(x) = (tt(i)-x)^2*(x-tt(i-3))/((tt(i)-tt(i-3))*(tt(i)-tt(i-2))*(tt(i)-tt(i-1))) + ...
            (tt(i+1)-x)*(x-tt(i-2))*(tt(i)-x)/((tt(i)-tt(i-2))*(tt(i)-tt(i-1))*(tt(i+1)-tt(i-2))) + (tt(i+1)-x)^2*(x-tt(i-1))/((tt(i+1)-tt(i-2))*(tt(i+1)-tt(i-1))*(tt(i)-tt(i-1)));

    p4(x) = (tt(i)-x)^3/((tt(i)-tt(i-3))*(tt(i)-tt(i-2))*(tt(i)-tt(i-1)));

    px(x) = (xx(i)*p1(x)+xx(i-1)*p2(x)+xx(i-2)*p3(x)+xx(i-3)*p4(x))/(p1(x)+p2(x)+p3(x)+p4(x));
    xxx = vpa(subs(px,x,ttt));
    py(x) = (yy(i)*p1(x)+yy(i-1)*p2(x)+yy(i-2)*p3(x)+yy(i-3)*p4(x))/(p1(x)+p2(x)+p3(x)+p4(x));
    yyy = vpa(subs(py,x,ttt));
    plot(xxx,yyy);
    hold on
    %plot([xx(i+1),xx(i+2)],[yy(i+1),yy(i+2)])
    %hold on
end