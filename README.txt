>> Introduction <<

This project is a desktop application for gel electrophoresis image analysis. As discussed in earlier reports, 
gel electrophoresis is a technique used in molecular biology and synthetic biology to determine the composition 
of a DNA, RNA or protein mixtures. The composition is determined by how these structures travel through a porous 
gel. Long, branched or looped structures tend to travel slower than short and straight structures. The main goal 
of this desktop application is to automate gel image analysis, thus optimizing experiment analysis in biology and 
synthetic biology. 
The scope of this desktop application includes the main deliverables:
1)  Loading Gel Image and changing image settings, such as contrast, brightness, cropping, color inversion, image 
flipping, etc;
2) Linearization of .gel (TIFF extension) files;
3)  Automated detection of lanes in gel;
4)  Automated lane labeling;
5)  Generation of graph with intensity peaks of bands across each lane;
    a.	Baseline correction;
    b.	Area calculation of each peak allowing user to choose bounds of integration;
    c.	Concentration profile per lane and across all lanes;
6) Speckle Removal;

>> Important Notes <<

-- The expected outputs (diagrams) of each of the following steps can be found in the "Expected Outputs.pdf" file;
-- Our code runs fully in Windows environment;
-- Use Qt Creator 4.1.0 (Community) to load our project;
-- To load our project, clone our entire folder and double click on 'ccc.pro'
        - Our original github repository can be found here: https://github.com/akirasan1992/Cproject
        - This will open our entire project in Qt creator.
        - Change to 'release' and make sure 'shadow build' is not checked;
        - Press play and start playing with our GUI (steps outlined below)




>> Instructions for Application Use <<



1) The user must load an image by clicking on the "Load Image" button.
        1.1. This allows for .jpeg, .jpg, .png and .gel images to be loaded
        1.2 Input files can be found in our "Input files" folder

2) .gel images must be linearized before moving forward with the software. After loading the .gel image, click on "linearize".
        2.1 .gel image format is an extension to the industry-standard TIFF file format. If the MD FileTag tag has value 2 
        (Square root data format), it is not regular grayscale, it is a scaled square root of grayscale and it must be
        linearized for correct quantification of pixel intensity.
        2.2 a .gel file can be found in the "Input files" folder and it is named "Gel file.gel"


3) The "Invert Colors" button is optional. This button simply inverts the colors in the image.

4) The "Crop" button (obviously) crops the image and is optional. 
        4.1 First click on the 'Crop' button  and it will go flat when it is selected;
        4.2 A rubber band will show up when you click and drag in the image;
        4.3 Let go of the rubber band to select area to be cropped.

5) The 'Reset' button resets any changes in the image settings.

6) The 'Undo' button reverses your last action in image editing.

7) The Horizontal and Vertical Flip buttons are optional.
        7.1 These buttons simply flip the image vertically and horizontally

8) 'Brightness' and/or 'Contrast' buttons and/or sliders are also optional
        8.1 First click the Brightness and/or Contrast button(s). These buttons will go flat when selected;
        8.2 After the button(s) is/are selected, adjust the slider(s) to change brightness and/or contrast settings.

9) 'Remove Specks' button is also optional and will remove specks/smudges on your gel image.
        9.1 By clicking on this button, two windows will pop up:
                9.1.1 Window #1: Speck Threshold -> How big does the speck need to be with respect to the band width to be removed? 0 - 100%
                9.1.2 Window #2: Dark Threshold 
        9.2 A input file for this function can be found in our "Input files" folder and it is called "gel with specks.jpg"
                9.2.1 Make sure to invert the colors before proceding with remove specks;
                9.2.2 Click on "Remove Specks" and don't change the default values in the pop-up boxes.

10) Now you are ready to play with the graphing tools of our GUI.

11) Detect lanes is mandatory.
	11.1 It detects dark bands from light background. Depending on the image loaded, you may have to inverse colors before detect lanes.
        11.1 If you are using a .gel image, you must linearize, invert the colors and crop the image before clicking on "detect lanes".
        11.2 The easiest file to visualize is "linearized file.jpg" in our "Input files" folder.
        11.2 You must detect lanes before you move on to other graphical tools. If you accidentally click on other buttons underneath it, a warning message will pop up.
        11.3 Type the number of lanes in the gel. "GEL file.gel" and "linearized file.jpg" both have 4 lanes, while "gel with specks.jpg" has 12 lanes.

12) Label lanes is optional but recommended.
        12.1 After clicking on "detect lanes", click on "label lanes".
        12.2 Each lane will be labeled starting at 1, from left to right.
	12.3 If you wish to draw a lane and analyze it later, it is better to label lanes because draw lanes requires the lane number.

13) Draw lanes comes after "Label lanes"
        13.1 After clicking on "label lanes", click on "draw lanes”.
        13.2 A window will pop up asking you which lane to draw on the intensity plot.

14) Draw all lanes gives you the option to plot all lanes at the same time.
	14.1 It is designed for visually compare all lanes so you can not use further analysis functions on the intensity graphs it produces.
	14.2 It clears last graph and settings.
	14.3 Each plot has a different color.

15) "Clear" button clears the lane labels from the image.

16) Baseline, upper bound and lower bound are the bounds of integration of the graph.
        16.1 These tools will enable you to calculate the area of each intensity peak (or all of them if you want) in the graph.
        16.2 In your mind, choose a peak you'd like to calculate the area of.
        16.3 Click on the "Baseline" button, then click and drag the horizontal red line on the graph to determine the bottom boundary of integration.
        16.4 Click the "Baseline" button again to lock the position of the bottom boundary. Everything under that line will be removed instantly.
        16.5 Click the "Upper bound" button, then click and drag the vertical green line on the graph to determine the rightmost boundary of integration.
        16.6 Click the "Upper bound" button again to lock the position of the rightmost boundary.
        16.7 Click the "Lower bound" button, then click and drag the vertical red line on the graph to determine the leftmost boundary of integration.
        16.8 Click the "Lower bound" button again to lock the position of the leftmost boundary.
	16.9 You can always click and drag lines several times before click on the function button to finalize.
        16.10 Click the "Calculate area" button to calculate the area on the peak(s) enclosed by the boundaries.
	16.11 Place the upper bound on the right of lower bound or the integration will result in 0.

17) Normalize button
	17.1 It normalizes the intensity graph so you can get a sense of how much percentage an interested peak contributes to the whole lane.
	17.2 You can check if a graph is normalized by calculating area and see if that equals to 1.

18) Message box displays error message. If you click on a button but nothing happens, check if the message box says anything.