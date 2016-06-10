close all;clc;
if (exist('S','var'))              %�ˬdS��data�ܼƬO�_�s�b�A�p���N�|�۰ʲM��
    fclose(S);
    clear S;
end
S = serial('COM11');                %***S��serial port
S.BaudRate = 115200;
fopen(S);

dataLength = 40000;

while(S.BytesAvailable == 0)        %read from the input buffer,�P�_s�O�_��Data�i��
end

rightData = [];                          %�NData�M��
leftData = [];
for i = 1:dataLength
    if mod(i, 2) == 1
      rightData = [rightData;str2double(fgets(S))];
    else
      leftData = [leftData;str2double(fgets(S))];
    end
end
fclose(S);%%[1 2; 3 4]
clear S;

plot(rightData, leftData);

% leftData = leftData./1000;
% test = diff(leftData).*200;
% hold on;
% plot(test);
% plot(leftData);

% test = zeros(1,length(leftData));
% threshold = pi;
% for i = 1:length(leftData)-1
%     test(i) = leftData(i+1)-leftData(i);
%   if test(i) > threshold
%     test(i) = test(i) - 2*pi;
%   end
%   if test(i) < -threshold
%     test(i) = test(i)+2*pi;
%   end
%   if test(i) > threshold
%     test(i) = test(i)-2*pi;
%   end
%   if test(i) < -threshold
%     test(i) = test(i)+2*pi;
%   end
%   test(i) = test(i)*200;
% end

