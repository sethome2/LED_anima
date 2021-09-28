# LED_anima
This lib allow you config different light strip anima by json or code.
![LED_animaLogo](https://github.com/sethome2/LED_anima/blob/main/LED_animaLogo.jpg)

___
# Thanks 3rd Libs and Their Author(s)
Thanks Configor writen by Nomango, Which is very easy and lightful json lib use MIT lincense.

LED_anima use it to parse the json string.

[GitHub link](https://github.com/Nomango/configor)
___
# How it work?
LED_anima is divide animation into two categories,one is <strong>ColorAnima</strong>, anthor one is <strong>LEDsAnima</strong>.

LED strip will be group to diffierent area(one LED can belong more than one area). In single frame,<strong>ColorAnima</strong> is the first calculate(or update).

ColorAnima will provide the frame color.And than, <strong>LEDsAnima</strong> will organize the LEDs show some Anima that color is base <strong>ColorAnima</strong> provide.

In some <strong>LEDsAnima</strong>, it maybe modify the frame color.

More infomation in the README and code.

___
# How to use?
Please see the smallest example:

___
# ColorAnima Info
1. alwaysON
It will show the color is you set.
2. rainbow

___
# Version List
TO DO: Organize the code to more expansive and understandble.

Ver 0.1:
1. Basic functions ware verify, no menmoy link.

