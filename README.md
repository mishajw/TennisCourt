# Tennis Court Line Detector and Identifier

Written as part of a task set by Hawk-Eye Innovations, where the goal is to detect the lines on a Tennis Court and label them correctly. The result should be a CSV detailing points on all the lines.

I chose this project, despite it being one of the hardest of the selection, because it involves visual recognition - one of the main aspects of Hawk-Eye that inspired me to apply. Despite me not being as familiar with C++ as I am with other languages, this has been a great learning experience with both C++ and OpenCV.

The structure of the program is split into three main sections.

##1. Line detection

Line detection was fairly straight-forward, with just applications of noise removal and edge detection filters supplied by OpenCV. However, using Hough transform resulted in more lines than desired. After tweaking the thresholds and such, I decided to apply K-means clustering to the lines, manually passing in the amount of lines expected. This misconstrued the original lines too much, but applying with a K of double the lines expected still decreased the amount of lines without damaging their accuracy. If I had more time, I would've worked on this K-means, as it would've dramatically improved the perceived lines.

##2. Line identification

The line identification was a more challenging (and fun!) section. My original idea was a recursive one, where each line would identify it's "neighbours", and depending on where they were positioned, guess what kind of court line it was. It would then check its neighbour's types, and see if that matched up with its own. However, once again due to time constraints, I decided to go for a simpler although less robust solution - although the unfinished source code for this can still be found in `LineIdentifier.cpp`.

The simpler solution was to separate the lines into vertical and horizontal. By hard-coding in the types of lines and where they would be positioned across the court, it is very easy to identify which lines are which by looking at their position relative to other lines.

##3. Formatting for CSV

This part was very simple, and all it required was to iterate over the lines and place these into a correctly formatted string.

###Conclusion
This was a very enjoyable task, and I plan to continue it when I have the free time. The main focuses would be improving the K-means clustering, and implementing the more complex and robust recursive line detection. As I am taking a module specifically directed at C++ next semester, I am sure the usage of C++ specific paradigms would improve.
