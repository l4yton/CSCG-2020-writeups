# Follow The White Rabbit - Cave

## Solution

Since I am running Linux and the game is basically non-responsive in a Windows VM, I tried to find other ways to solve the challenge without having to actually run the game. Because the game was made in Unity, I
searched for rescources on hacking Unity Games and came across this github repository: https://github.com/imadr/Unity-game-hacking. 
<br/> <br/>
There are multiple tools listed that can extract pictures and other stuff from unity assets files. I went for [UtinyRipper](https://github.com/mafaca/UtinyRipper), but
every other tools on the list probably could've done the job.
<br/>
All I had to do from there was to drag the files into the friendly GUI of UtinyRipper and search for interesting images in the extracted files:
<br/> <br/>
![](UtinyRipperFlag.png)
<br/> <br/>
Flag: `CSCG{data_mining_teleport_or_gravity_patch?}`

## Mitigation

Unity assets files can be encrypted, it is noted however that a user determined to extract assets, will most likely be able to. More information can be found here: https://docs.unity3d.com/540/Documentation/Manual/protectingcontent.html
