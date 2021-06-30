Few weeks ago, a famous software company has upgraded its instant messaging software. A ranking system was released for user groups. Each member of a group has a level placed near his nickname. The level shows the degree of activity of a member in the group.

Each member has a score based his behaviors in the group. The level is determined by this method:
Level | Percentage  | The number of members in this level
----- | ----------  | -----------------------------------
LV1 | /	| All members whose score is zero
LV2	|/	|All members who can not reach level 3 or higher but has a positive score
LV3	|30%|	⌊(The number of members with a positive score) * 30%⌋
LV4	|20%|	⌊(The number of members with a positive score) * 20%⌋
LV5	|7%|	⌊(The number of members with a positive score) * 7%⌋
LV6	|3%|	⌊(The number of members with a positive score) * 3%⌋

 is the maximum integer which is less than or equal to
 
 The member with the higher score will get the higher level. If two members have the same score, the earlier one who joined the group will get the higher level. If there is still a tie, the user with smaller ID will get the higher level.
Please write a program to calculate the level for each member in a group.

Input

There are multiple test cases. The first line of input is an integer <var>T</var> indicating the number of test cases. For each test case:

The first line contains an integer <var>N</var> (1 <= <var>N</var> <= 2000) indicating the number of members in a group.

The next <var>N</var> lines, each line contains three parts (separated by a space):

The ID of the i-th member <var>Ai</var> (0 <= <var>Ai</var> <= 1000000000). The ID of each member is unique.
The date of the i-th member joined the group, in the format of YYYY/MM/DD. The date will be in the range of [1900/01/01, 2014/04/06].
The score <var>Si</var> (0 <= <var>Si</var> <= 9999) of the i-th member.

Output

For each test case, output <var>N</var> lines. Each line contains a string represents the level of the i-th member.

Sample Input
