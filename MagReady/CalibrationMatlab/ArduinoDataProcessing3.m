clear all;
clc;


%ellipsoid limits
max_ell= 75000;

%local mag field at 
%https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml#igrfwmm
localMag = 49254.5;

%data read from the text file
textFile = 'test.txt';
fID = fopen(textFile,'r');
data = fscanf(fID,'%f\t%f\t%f',[3,inf]);
fclose(fID);

v=proc(data);%ellipsod fitting

A=[v(1),v(6),v(5);v(6),v(2),v(4);v(5),v(4),v(3);];
p=inv(A)*[(-v(7)),(-v(8)),(-v(9))]';%offset calculation
[Vm,~] = eig(A);

figure(1);
%hard iron (offset) correction
data2 = data - p;
%reprocess data
v2 =  proc(data2);
%A2=[v2(1),v2(6),v2(5);v2(6),v2(2),v2(4);v2(5),v2(4),v2(3);];

%plot data
hold on
ellPlot(v2,max_ell);
plot3(data2(1,:),data2(2,:),data2(3,:),'ko')
localAxis(Vm,max_ell)
hold off

%mapping local ellipsoid axis onto global axis---------bug
%bias = inv((Vm));
data3 = inv((Vm)) * data2;
%getting new axis
v2_1 =  proc(data3);
A2=[v2_1(1),v2_1(6),v2_1(5);v2_1(6),v2_1(2),v2_1(4);v2_1(5),v2_1(4),v2_1(3);];
[Vm2,~] = eig(A2);
%replot
figure(2)
hold on
ellPlot(v2_1,max_ell);
plot3(data3(1,:),data3(2,:),data3(3,:),'ko')
localAxis(Vm2,max_ell)
hold off
%normalising quadric equation
v3=v2_1./v2_1(10);

%soft iron adjustment (morphing into sphere)
newa=sqrt(1/abs(v3(1)));
newb=sqrt(1/abs(v3(2)));
newc=sqrt(1/abs(v3(3)));
data4(1,:) = (data3(1,:)./newa)*localMag;
data4(2,:) = (data3(2,:)./newb)*localMag;
data4(3,:) = (data3(3,:)./newc)*localMag;

%reangle data
data4 =Vm* data4;

%getting new axis
v4=proc(data4);
A4=[v4(1),v4(6),v4(5);v4(6),v4(2),v4(4);v4(5),v4(4),v4(3);];
[Vm4,~] = eig(A4);


%replotting
figure(3)
hold on
ellPlot(v4,max_ell);
plot3(data4(1,:),data4(2,:),data4(3,:),'ko')
localAxis(Vm4,max_ell)
hold off

%bias calculation for arduino code
%{
bias = Vm;
bias2(1,:) = (bias(1,:)./newa)*localMag;
bias2(2,:) = (bias(2,:)./newb)*localMag;
bias2(3,:) = (bias(3,:)./newc)*localMag;
%}

bias3=(data2)/(data4);

%bias 4 is what we use for biasing arduino code
bias4=inv(bias3);

%use the values from bias.txt as they are of
%greater precision
fID2 = fopen('bias.txt','w');
fprintf(fID2,'Hard iron bias:\n');
fprintf(fID2,'%.8f\t%.8f\t%.8f\n\n',p);
fprintf(fID2,'Soft iron bias:\n');
fprintf(fID2,'%.8f\t%.8f\t%.8f\n',bias4);
fclose(fID2);


function localAxis(V,max_lim)%plots local axis
gridlim=max_lim*(4/3);
[~,grid]=meshgrid(1:3,-gridlim:gridlim/100:0);
[~,grid2]=meshgrid(1:3,0:gridlim/100:gridlim);
Xgrid=(grid*diag(V(:,1)));
Ygrid=(grid*diag(V(:,2)));
Zgrid=(grid*diag(V(:,3)));

Xgrid2=(grid2*diag(V(:,1)));
Ygrid2=(grid2*diag(V(:,2)));
Zgrid2=(grid2*diag(V(:,3)));

plot3(Xgrid(:,1),Xgrid(:,2),Xgrid(:,3),'r');
plot3(Ygrid(:,1),Ygrid(:,2),Ygrid(:,3),'g');
plot3(Zgrid(:,1),Zgrid(:,2),Zgrid(:,3),'b');

plot3(Xgrid2(:,1),Xgrid2(:,2),Xgrid2(:,3),'k');
plot3(Ygrid2(:,1),Ygrid2(:,2),Ygrid2(:,3),'c');
plot3(Zgrid2(:,1),Zgrid2(:,2),Zgrid2(:,3),'m');
end