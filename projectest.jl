using LinearAlgebra, Plots
pyplot()

delta = 0.05
xmin = 0.0
xmax = 10.0
ymin = 0.0
ymax = 10.0
nx = Int64((xmax - xmin) / delta)
ny = Int64((ymax - ymin) / delta)
nstep = 100

potential = zeros(Float64, nx, ny)

ii = 1
for jj in 1:ny
    potential[ii, jj] = 1.0
end


for istep in 1:nstep
    for ii in 2:nx-1
        for jj in 2:ny-1
            potential[ii, jj] = (potential[ii+1, jj] + potential[ii-1, jj] + potential[ii, jj+1] + potential[ii, jj-1]) / 4.0
        end
    end
end

surface(potential)
