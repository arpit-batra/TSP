import matplotlib.pyplot as plt

def plotTSP(path, points, num_iters=1):

    """
    path: List of lists with the different orders in which the nodes are visited
    points: coordinates for the different nodes
    num_iters: number of paths that are in the path list
    
    """

    # Unpack the primary TSP path and transform it into a list of ordered 
    # coordinates

    x = []; y = []
    for i in paths[0]:
        x.append(points[i][0])
        y.append(points[i][1])
    
    plt.plot(x, y, 'co')

    # Set a scale for the arrow heads (there should be a reasonable default for this, WTF?)
    a_scale = float(max(x))/float(100)

    # Draw the older paths, if provided
    if num_iters > 1:

        for i in range(1, num_iters):

            # Transform the old paths into a list of coordinates
            xi = []; yi = [];
            for j in paths[i]:
                xi.append(points[j][0])
                yi.append(points[j][1])

            plt.arrow(xi[-1], yi[-1], (xi[0] - xi[-1]), (yi[0] - yi[-1]), 
                    head_width = a_scale, color = 'r', 
                    length_includes_head = True, ls = 'dashed',
                    width = 0.001/float(num_iters))
            for i in range(0, len(x) - 1):
                plt.arrow(xi[i], yi[i], (xi[i+1] - xi[i]), (yi[i+1] - yi[i]),
                        head_width = a_scale, color = 'r', length_includes_head = True,
                        ls = 'dashed', width = 0.001/float(num_iters))

    # Draw the primary path for the TSP problem
    plt.arrow(x[-1], y[-1], (x[0] - x[-1]), (y[0] - y[-1]), head_width = a_scale, 
            color ='g', length_includes_head=True)
    for i in range(0,len(x)-1):
        plt.arrow(x[i], y[i], (x[i+1] - x[i]), (y[i+1] - y[i]), head_width = a_scale,
                color = 'g', length_includes_head = True)

    #Set axis too slitghtly larger than the set of x and y
    print (max(x),max(y))
    plt.xlim(min(x), max(x)*1.1)
    plt.ylim(min(y), max(y)*1.1)
    plt.show()


if __name__ == '__main__':
    # Run an example
    
    # Create a randomn list of coordinates, pack them into a list
    points = []
    n=int(input())
    for i in range(0, n):
        A=input().split()
        x_cor=float(A[0])
        y_cor=float(A[1])
        points.append((x_cor, y_cor))

    print ("bangaya")
    
    path1 = [487,281,318,175,221,52,97,232,385,260,299,197,71,146,264,475,144,65,95,100,24,426,354,132,238,217,348,35,94,86,148,23,291,245,307,60,320,338,420,141,429,243,324,37,9,102,379,434,468,289,486,361,51,19,182,394,465,296,360,481,211,104,88,111,209,99,244,160,454,380,234,226,400,2,447,229,28,414,273,294,186,44,6,422,450,496,183,125,323,472,257,489,356,91,397,461,349,49,342,372,266,335,222,153,90,17,279,198,446,120,423,70,26,206,332,157,464,265,152,81,240,27,176,275,497,455,442,5,55,147,165,445,63,395,300,355,53,123,334,150,72,171,377,87,80,457,359,317,253,292,149,258,170,277,326,252,301,483,366,315,357,121,47,403,204,20,276,77,122,478,269,255,415,131,490,365,32,56,280,386,340,331,485,341,311,375,68,347,363,108,30,207,367,484,66,374,172,469,124,136,140,237,467,339,427,282,456,411,297,201,473,410,337,325,193,139,220,295,443,215,313,194,474,383,284,118,376,437,103,439,494,393,438,96,190,177,210,137,413,173,261,84,353,242,432,188,46,110,316,419,392,16,435,303,128,476,329,174,495,112,298,308,314,239,463,85,196,268,107,105,11,15,89,214,10,179,29,189,61,154,185,346,178,69,470,498,491,164,285,134,328,192,263,388,43,151,13,278,155,235,135,459,130,251,350,452,184,477,225,399,33,218,114,14,312,159,167,22,161,62,57,31,371,169,310,351,441,58,287,246,54,436,4,345,41,48,162,138,381,302,39,75,327,21,129,127,223,322,262,283,8,460,444,92,358,440,480,479,425,417,293,449,407,369,163,330,304,187,390,101,40,352,119,453,370,433,67,117,74,0,249,195,466,109,64,319,50,168,166,305,38,471,191,203,73,231,431,405,25,79,364,227,389,158,458,248,492,34,336,362,241,200,321,391,493,247,36,202,219,145,208,83,406,384,7,216,133,59,1,230,224,404,290,116,106,82,3,42,93,142,156,309,199,387,143,382,18,462,126,306,344,270,408,286,430,180,409,368,418,288,233,12,402,250,76,212,378,98,267,271,213,488,272,412,448,256,45,274,428,259,115,343,482,401,78,205,236,333,421,396,416,373,228,451,113,424,254,181,398,499]

    # Pack the paths into a list
    paths = [path1]
    
    # Run the function
plotTSP(paths, points, 1)