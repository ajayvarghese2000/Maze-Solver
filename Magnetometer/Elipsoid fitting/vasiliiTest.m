clear all;
clc;

a=10; %semi major
b=2;%semi minor
x0=0;
y0=0;
the = pi/4;
dx=0.1;
x=-10:dx:10;
%Constants
A=a^2*(sin(the))^2+b^2*(cos(the))^2;
B=2*(b^2-a^2)*sin(the)*cos(the);
C=a^2*(cos(the))^2+b^2*(sin(the))^2;
D=-2*A*x0-B*y0;
E=-B*x0 - 2*C*y0;
F=A*x0^2+B*x0*y0+C*y0^2-a^(2)*b^(2);

temp=sqrt((B*x+E).^2 - 4*C*(A*x.^2+D*x+F));
y1=((-B*x - E) + sqrt((B*x+E).^2 - 4*C*(A*x.^2+D*x+F)))/(2*C);
y2=((-B*x - E) - sqrt((B*x+E).^2 - 4*C*(A*x.^2+D*x+F)))/(2*C);
y1=real(y1);
y2=real(y2);
test=((length(x))/2);


noiseIntensity=0.1;
for v = 2:(length(x)/2)
    if y1(v)==y2(v)
       y1(v-1)=NaN;
       y2(v-1)=NaN;
    else
       y1(v-1)=y1(v-1)+randn(1)*noiseIntensity;
       y2(v-1)=y2(v-1)+randn(1)*noiseIntensity;
    end
end
for w =((length(x))/2-0.5):1:(length(x)-1)
    if y1(w)==y2(w)
       y1(w+1)=NaN;
       y2(w+1)=NaN;
    else
       %y1(w+1)=y1(w+1)+randn(1)*noiseIntensity;
       %y2(w+1)=y2(w+1)+randn(1)*noiseIntensity;
    end
end

randn(size(1))*noiseIntensity;
randn(size(1))*noiseIntensity;
%{
%---------------------------------------
y=sqrt((a^2*b^2-a^2*(x-x0).^2)/b^2)+y0;
y=real(y);
hold on 
plot(x,y,'go');
plot(x,-y,'go');
hold off
%----------------------------------
%}
hold on
xlim([-10 10])
ylim([-10 10])
plot(x,y1,'bo');
plot(x,y2,'bo');
hold off