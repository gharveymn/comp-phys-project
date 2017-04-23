fileID = fopen('map2.txt', 'r');
formatSpec = '%f';
data = fscanf(fileID,formatSpec);
x_min = data(1);
x_max = data(2);
y_min = data(3);
y_max = data(4);
num_squares = data(5);
figure
axis([x_min x_max y_min y_max]);
%grid on;
%grid minor;

for i=6:4:size(data,1) - 3
    x = data(i);
    y = data(i+1);
    l = data(i+2);
    w = data(i+3);
    rectangle('Position', [x y l w], 'FaceColor', 'y');
end;

fileID = fopen('tree.txt', 'r');
formatSpec = '%f';
data = fscanf(fileID, formatSpec);
i = 1;
colours = ['m','c','r','g'];
while i < size(data,1) - 4
    x = data(i);
    y = data(i + 1);
    l = data(i + 2);
    w = data(i + 3);
    
    x = x - l;
    y = y - w;
    l = 2*l;
    w = 2*w;
    
    num_adjacent = data(i+4);
    i = i + 5;
    i = i + num_adjacent*4;
    rectangle('Position', [x y l w], 'FaceColor', 'none');
end;