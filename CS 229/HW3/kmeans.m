
tol = 10^-6;
max_iters = 300;
num_clusts = 16;

%%Initializing Centroids
centroids = zeros(num_clusts,3);
for i=1:num_clusts
    r = unidrnd(size(A,1),1,1);
    c = unidrnd(size(A,2),1,1);
    centroids(i,:) = A(r,c,:);
end

%Step 2 - Repeating until convergence
c_assignments = zeros(size(A,1),size(A,2));
delta = 1;
iter = 1;
while delta > tol && iter < max_iters
    old_centroids = centroids;
    %Iterate through each pixel and find cluster assignment
    for i = 1:size(A,1)
        for j = 1:size(A,1)
            pixel_rgb = [A(i,j,1) A(i,j,2) A(i,j,3)];
            %For a pixel get the cluster that has min distance to that pixel
            min_dist = norm(centroids(1,:) - pixel_rgb, 2);
            c_assignments(i,j) = 1;
            for k = 1:size(centroids,1)
                dist = norm(centroids(k,:) - pixel_rgb, 2);
                if dist < min_dist
                    min_dist = dist;
                    c_assignments(i,j) = k;
                end
            end
        end
    end
    
    %Recompute centroids
    %Saving old centroids to compute change later
    for k = 1:size(centroids,1)
        %Getting sum of rgb values for each pixel beloing to centroid and
        %num of pixels
        rgb_sums = zeros(1,3);
        num_pixels = 0;
        for i = 1:size(A,1)
            for j = 1:size(A,1)
                if c_assignments(i,j) == k
                    pixel_rgb = [A(i,j,1) A(i,j,2) A(i,j,3)];
                    rgb_sums = rgb_sums + pixel_rgb;
                    num_pixels = num_pixels + 1;
                end
            end
        end
        
        %Recomputing centroid with means of RGB values of pixels belonging
        %to centroid.
        if num_pixels ~= 0
            centroids(k,:) = rgb_sums/num_pixels;
        end
    end
    delta = norm(centroids - old_centroids, 2);
    delta 
    iter
    iter = iter + 1;
end

%Compress A
compressed = A;
for i = 1:size(A,1)
    for j = 1:size(A,2)
        for k = 1:size(centroids,1)
            if c_assignments(i,j) == k
                compressed(i,j,:) = centroids(k,:);
            end
        end
    end
end

            
        