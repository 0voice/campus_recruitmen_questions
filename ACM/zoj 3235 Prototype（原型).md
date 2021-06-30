# 题目
Prototype is a 3D game which allow you to control a person named Alex with much super ability to finish missions with gut along. 
Alex has the abilitiy to glide in the sky. What's more, he can make at most 3-level glide, which means before he lands at the ground,
he has two chances to adjust and perform another glide. We assume that each time he perform a glide, his vertical speed become zero and glide forward with a new speed.
And the orbit will be a parabola due to the gravity.

![image](http://uploadfiles.nowcoder.com/probs/acm/zoj_2225desc_0.jpg) <br>
To make the problem easier, we now only consider at most 2-level glide. The binomial coefficient of the mathematical equation of the fist glide will be given as -a and the second will be -b, which means the formulations are (y - y0) = -ax2 and (y - y0) = -b(x - x0)2. As the picture above, Alex perform a glide from the top of Building1, make a 1-level or a 2-level glide and lands exactly at point B. What's more, there is Building2 standing between Building1 and point B. Alex has to avoid crashing onto it.
Input

There are no more than 15 cases. Proceed till the end of file.
Each case contains only one line of six real number h1 , h2 , d1 , d2 , a, b. h1 is the height of Building1, h2 is the height of Building2, d1 is the X-distance between Building1 and Building2, d2 is the X-distance between point B and Building1. These four numbers are in [0, 1000] , and satisfies d1 < d2. And a and b are in (0, 1000].

Output

If it is possible for Alex to land exactly on point B, print Yes, otherwise print No.

Sample Input

* 25 1 6 7 1 1
* 4 3 1 2 1 1  <br>
Sample Output <br>
* Yes
* Yes

HINT

In case 2, Alex just glide over the building2 and do not crash onto it.
