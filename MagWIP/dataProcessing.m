clear all
clc

fID = fopen('comp_data.txt','r');
data = fscanf(fID,'%f %f',[2,inf]);
fclose(fID);
x=data(1,:);
y=data(2,:);
plot(x,y)