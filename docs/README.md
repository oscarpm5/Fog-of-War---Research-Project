I am [Oscar Pérez](https://www.linkedin.com/in/oscar-pérez-martín-94a3a5196/), student of the [Bachelor’s Degree in
Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s
subject Project 2, under supervision of lecturer [Marc Garrigó](https://www.linkedin.com/in/mgarrigo/).

You can check the project repository [HERE](https://github.com/oscarpm5/Fog-of-War---Research-Project) to get acces to the source files and the project website [HERE](https://oscarpm5.github.io/Fog-of-War---Research-Project/) for a detailed article about Fog of War in Videogames.

# Introduction
In this document we will take a look at what is Fog ow War, the different aproaches used in videogames, the different types of fog of war tat exist and we will finally explain how to implement it in our own videogame using some exercises to better comprehend the process.

## Terminology - What is Fog of War?
Fog of war, FoW from now on, is a term used in armed conflicts that was first described in the book "The Fog of War" by Carl von Clausewitz. The expression was later used by generals during the 1st and the 2nd World War and refers to the uncertainty in situational awareness (that is the perception of environmental elements and events, the comprehension of their meaning, and the projection of their future status) experienced by participants in military operations.

In videogames this expression is used to describe unexplored or hidden terrain or map areas. It is mostly used in strategy and roleplay videogames: the former uses it to hide information about what other players are doing and thus making the game more interesting by forcing the player to take risks, gather intel or predict what others might do. The latter uses FoW to tell the players that, although they might have discovered a certain area of the playable map, they still have much more to discover and thus encourage exploration.

<p align="center">
<img src="https://raw.githubusercontent.com/oscarpm5/Fog-of-War---Research-Project/master/docs/Images/Empire%20VideoGame.png" width="700">
</p>

This image shows the videogame "Empire" by Walter Bright, released in 1977, being the first videogame that used FoW.

## Types
With only two basic parameters we can define almost every videogame's FoW:

### Fog / Fog & Shroud
This first parameter depends on the kind of videogame we are willing to make and its intended features. Basically, games with FoW can be divided into two: the ones with only fog and the ones with fog and shroud.
The ones with only fog are the ones that do not care so much about exploring, they instead focus on hidding information. As a player you see all the terrain but you cannot see the enemies or buidings, or at least not in real time but a representation of their state the last tile you saw that area.

An example of a game that consist ony of visible areas and foggy areas is League of Legends. It comes up with two interesting additions to the system: bushes that are always fogged from the outside and wards that clear vision for you.

//League of Legends image Here

The ones with fog and shroud have two types of fog instead of one, where the fog consist of areas that have been discovered but are not visible at the moment and thus the things seen in those areas are the ones players saw last time they were in there and the shroud consists of unexplored territory, usually represented with a black texture representing a void. Iron Marines is a great example of a game with this type of FoW:

<p align="center">
<img src="https://raw.githubusercontent.com/oscarpm5/Fog-of-War---Research-Project/master/docs/Images/Iron%20Marines%20FoW%20Concept%20Art.png" width="700">
</p>
<p align="center">
<img src="https://raw.githubusercontent.com/oscarpm5/Fog-of-War---Research-Project/master/docs/Images/Iron%20Marines%20In-Game%20FoW.png" width="700">
</p>

There is also a 3rd type, not that common nowadays but it certainly was in the past: a mix between fog and fog & shroud. That is only shroud; where the player has full vision of the explored territories and knows nothing about unexplored areas, with a hard transition between full visible and pitch black. Dune 2 is a great example of it:

<p align="center">
<img src="https://raw.githubusercontent.com/oscarpm5/Fog-of-War---Research-Project/master/docs/Images/Dune%202%20FoW.gif" width="700">
</p>

We find the same type of fog in Warcraft: Orcs and Humans
<p align="center">
<img src="https://raw.githubusercontent.com/oscarpm5/Fog-of-War---Research-Project/master/docs/Images/Warcraft_Orcs%20and%20Humans%20FoW.png" width="700">
</p>

### Chunky / Smooth
The second parameter will let us define how our FoW looks and feels.

While chunky fog is the easiest to implement it is also the less common to go with these days. That is due to the hard edges in the shape of squares that it forms that are not pleasing to see at all for the players. This happens because this kind of fog is conformed by an array or grid of usually two or three states (defined by an enumerator or a bool in case it is only two states) that describe if that position in the grid has been explored and if it is visible or not. When it is not visible a black square is drawn over the map or the map isn't drawn at all. The fog layer is usually printed to the screen at half opacity.

Here is an image of some testing done in Iron Marines so you can compare it with the look and feel that the two previous shown images of the same game have:

<p align="center">
<img src="https://raw.githubusercontent.com/oscarpm5/Fog-of-War---Research-Project/master/docs/Images/Iron%20Marines%20In-Game%20FoW%20CHUNKY.png" width="700">
</p>

And here is an example of what a chunky FoW system looks like in a modern game with 3D terrain:

<p align="center">
<img src="https://raw.githubusercontent.com/oscarpm5/Fog-of-War---Research-Project/master/docs/Images/Knights%20Merchant%20FoW%20CHUNKY.png" width="700">
</p>

Smooth FoW is a little bit harder to implement than the chunky one but it provides far better visuar results in 2D games nevertheless. There are many ways to get a cool looking smooth FoW ranging from methods like Bitmap Masking, blurring a FoW texture or using algorithms like the neighbour aware tile selection method and the marching squares to print only the fogged area into a texture. Some of those approaches will be covered more in depth below.

Here is an example of a game that uses smooth FoW and also fog & shroud: Age of Empires.

<p align="center">
<img src="https://raw.githubusercontent.com/oscarpm5/Fog-of-War---Research-Project/master/docs/Images/Age%20of%20Empires%20SMOOTH%20FoW.jpg" width="700">
</p>


# Different Approaches
Now that we understand what types of FoW exist, lets take a look on how do they work.
## Tile Grid Based
## Texture mask Based
## Raycasting (2D)


# Selected Approach


# More Documentation


# TODO's
## TODO 1

<details>
  <summary>Show Solution</summary>

</details>

## TODO 2

<details>
  <summary>Show Solution</summary>

</details>

## TODO 3

<details>
  <summary>Show Solution</summary>

</details>

## TODO 4

<details>
  <summary>Show Solution</summary>

</details>

## TODO 5

<details>
  <summary>Show Solution</summary>

</details>

## Optional Homework
## Possible Improvements
