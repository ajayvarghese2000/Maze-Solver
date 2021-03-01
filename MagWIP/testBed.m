clear all
clc 

pts = -5:0.01:5;
V=[12;13];
A=[9 ,1;-1 ,9];
b=(1/(sqrt(A(1,1)^2+A(2,1)^2)));
B=A.*b;
C=A*V;
D=B*V;

[~,grid]=meshgrid(1:2,pts);
Xgrid=(grid*diag(A(:,1)));
Ygrid=(grid*diag(A(:,2)));

%diag(D(:,2))



%Xgrid(:,2)
hold on
plot(Xgrid(:,1),Xgrid(:,2),'b')
plot(Ygrid(:,1),Ygrid(:,2),'r')

%plot(C(1),C(2),'bo')
plot(D(1),D(2),'ro')
plot(V(1),V(2),'go')
hold off