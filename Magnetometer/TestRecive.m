clear all
clc

arduino = serial('COM4','BaudRate',9600);
test=func(arduino,500);

function y=func(x,d)
y=linspace(1,d);
fopen(x);
    for i=1:length(y)
        y(i)=fscanf(x,'%f');
    end
fclose(x);

end