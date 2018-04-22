Isaac Calvis <br> <b> _Research : Fog Of War (FoW)_ <b/> <br/>

### Index

1. General Information
    * What’s FoW.
    * How it works.
    * Examples of games with FoW

2. Problems to implement FoW and how to solve it (using C++ & SDL)
    * Cover areas of the map in an opaque manner
    * Calculate the area (player coords) that player can see
    * How to use translucent areas (Alpha channel)
    * At translucent zones see terrain but not troops.
    * Save visited zones (to transform them to translucent)
    * Code optimization techniques

3. Previous necessities & Art techniques
    * Previous necessities
    * Art techniques

<br><br/>

## 1.1 What’s FoW

    FoW is a tool used in video games to limit the view of the player. It’s used in games like RTS or in games with 3rd 
    Person when you can’t see enemies or structs that aren’t near the player.

    We can say that we have 2 types of FoW, and they can combine. The first one, that block the vision of the player at 
    the far areas (from his point of view), and the second one, a translucent layer, where you can see the terrain but not 
    other things like units, structs, objects, etc… In a lot of games, the FoW is the first type, and when you discover 
    it, the area pass to be translucent.

    The knowledge of the areas can be stored or nor, that means that if you pass through a zone, when you go out of this, 
    the area will be in translucent FoW.

![FoW example](https://static1.squarespace.com/static/54c3fae6e4b0afdbad22d1b9/t/58a9c3ab44024386af6f0364/1487520707161/)

1.2 How it Works

    At last point, we saw that FoW have variations. First we could put the factor if it is translucent or opaque from the 
    beginning. Then we would have the factor of whether it is cumulative or not. We will assume that if it is cumulative, 
    the path we have already passed will be seen translucently.

    So we have a model to solve; first the map is opaque and we do not see anything, that where the character passes looks 
    perfectly close to the character, and when the character leaves, it is still seen translucently, the terrain and 
    structures are seen, but not the dynamic units, or the variation of the structures (if they are destroyed or new ones 
    are created).

    With this model we could make any variation to get any FoW. This FoW will work the same for all games, but for some 
    ways to optimize the code you will need to make variations for specific cases. As in the case where we can make units 
    appear anywhere on the map (you will see). The parameters of the FoW will be variable, the radius of the area we 
    discover, the size of the path we leave, etc...

1.3 Examples of games with FoW

    There are many games that use the FoW, but I try to put one in each genre or type of game (to see the variety).

    •RTS: FoW badge, there are several models, such as starcraft 2, where from the beginning you see the whole map 
    (translucent), and the only thing you do not see is your enemy (or mobile units or structures), where If there is a 
    trace of the structures but not of their modifications. And then we have other rts such as the Age of Empire 3 where 
    the unknown areas appear opaque, and once the area is discovered, it looks completely to the end of the game, you can 
    see all movements, including enemies.

    •MOBA & Arena: games like the League of Legends (MOBA) or the battlerite (Arena), use a translucent FoW, so you can 
    see the map (terrain), but not the npc's, objects or enemies (players). FoW does not disappear as you go through the 
    paths. It is used to increase voltage, stealth and strategy in games where the action predominates.

    •Action RPG: FoW also appears in games like Diablo 3, or Wastelands 2, action games with role components where you 
    move to large maps, where the FoW limits the entire map or makes the vision difficult.

    In summary, the FoW is used in many types and genres of games, and each one uses it in a different way.

<br><br/>

## 2. How to plan the FoW and Solve

    Here we only consider theoretically, the problems we will have to create a FoW.
    The problems will be:

    •Cover areas of the map in an opaque manner
    •Calculate the area around the player where everything is seen
    •Power to cover areas translucently (alpha channel)
    •In translucent areas see land but not troops
    •In translucent areas see structures (make a copy image)
    •Acquire the areas you've been through.
    •Code Optimizations

#### _First problem: Tap areas of the map_

    Covering an area of the map is not difficult, it is applied on a completely dark tile. To avoid creating a second list 
    full of tiles, we can find 2 solutions. First, do not create a second list, and each tile has an option to become 
    dark, and the second option, make a second list with 2/3... Bigger tiles, larger than the originals, in order to have 
    one Second much smaller list.

![imgp1](https://user-images.githubusercontent.com/25582479/38470631-0296c5d4-3b66-11e8-8203-a68164ad83c7.png)


    Tile Images by: Andy Buck -- 2006

#### _Second Problem: Calculate the area around the player where everything is seen_

    To calculate the area around the player, we'll do a function that is done at the every Update, and look at distance of 
    every tile with player, if the distance is less than the radius we'll change the alpha variable to 0, else, alpha will 
    be returned to 255 (remember we are using RGBA).
    To calculate the distance to player perfectly use pitagoras. SquareRoot(dX^2 + dY^2), in C++ it's like :
        sqrt (distanceX * distanceX + distanceY * distanceY)

                        
![tallp1](https://user-images.githubusercontent.com/25582479/38563710-cf350b6e-3cdd-11e8-9601-515e5d908f35.JPG)

#### _Third problem: How to cover areas translucently (alpha channel)_

    Bearing in mind that we are in SDL we will use their tools. There is the function:
    SDL_SetTextureAlphaMod (SDL_Texture * texture, uint8 Alpha);
    As you can see, you pass a texture already loaded, and you pass an alpha percentage (ranging from 0% to 100% - 0 to 
    255).
    This feature is already implemented in the Blit function (which you will have for the exercise)
    Blit (SDL_Texture *, x, y, & SDL_Rect, alpha).

    We will add a new int variable, named normalAlpha. This variable will start at 255 (black), and when the tile is 
    discovered (remember the 2nd problem), we'll change this variable to 255 / 2 (or else). Now, when the tile is not 
    inside the player range, well change the tile alpha to normalAlpha; alpha = normalAlpha.

![tallp2](https://user-images.githubusercontent.com/25582479/38563809-083810be-3cde-11e8-86f4-eea633f485af.JPG)

#### _Fourth Problem: In translucent areas see land but no troops_

    When applying alpha, you will see everything underneath, then, to avoid seeing enemy troops, objects, structures, etc 
    ... what we will do is culling, with visible areas.
    As our visible area is a circle, because "something" that a priori is not visible, it is not, it will be necessary to 
    verify if it is within the range of vision. This is done by looking that the distance between the objective and the 
    player is equal to or less than the range of vision, if the distance is bigger than the range don't print at screen.

![tallp3](https://user-images.githubusercontent.com/25582479/38563949-5db75842-3cde-11e8-83b3-e7415f48895c.gif)

#### _Fifth Problem: Acquire the areas you've been through_

    If we want to check if the tile is seen (discovered) or not (to draw a map or minimap with FoW, unlock something, 
    etc...), we only need to check the alpha of the tile list. 255-> not discovered 255 / 2 (or the translucent value we 
    have add)-> discovered but not seen, 0-> seen. To normalize this, we could use defines or enums.

#### _Code Optimizations_

    Execute the logic of the FoW less times. If the FoW runs regularly with the rest of the game's logic, it spends 
    resources that we can avoid spending. We can do that the logic of the FoW is executed 1 of every 6 times that the 
    logic is executed, for practical effects the player will almost not notice it.

    Do not update the FOW in case there is no movement. You can save the player's previous position, and if it is equal to 
    the current one, it has not moved, in this case, avoid calling the FoW to update it.

<br><br/>

## 3. Extra points, previous needs and Art

    At the artistic level: There are 2 techniques (that can be combined) to generate a more aesthetically 
    beautiful FoW. The 2 are explained in the "Link to Riot web (LoL) on their FoW" link (bibliography link), made by 
    Jaewon Jung, developer of the League of Legends.

    Gaussian Blur is a mathematical algorithm that diffuses an image.
    (Here I will not explain how to use it)

    This helps in a FoW since the tips or limits of the vision area are not so sharp. Applying it to as large as the ones 
    we use is not optimal, it would be best to use it with the following technique.

    Transform the visor field's limiting tile into smaller pieces:
    The tiles that are to the limit of the field of vision leave them in a 2x2, or 3x3 or more. And depending on your 
    colleagues, make these smaller tiles transparent, opaque or translucent (very clear example image in the link).

    To this, we will adapt (or add new concrete functions) to know the distance & print this smaller pieces. To create 
    this pieces, we will adapt to the function that decide if a tile is transparent or not, and put a new if. If distance 
    to player is equal to radius (remember all is done in local position for FoW_Tiles), set the concrete tile alpha to 0, 
    and create 'x' (depending the fractions you want to do) smaller tiles in a separated list (list to all smaller tiles), 
    and put it at the corret position. The functions we adapted to print smaller tiles, will use this 2nd list that 
    storage this smaller tiles.

![tallp4](https://user-images.githubusercontent.com/25582479/38622432-7439b40a-3da3-11e8-8ea5-f01cc5ba9b08.JPG)

References:
--------------------------------------------------------------------------------------------------------------------
Link to Wikipedia with information and description about the real FoW:

https://en.wikipedia.org/wiki/Fog_of_war
 
Link to the videogames new site “GiantBomb” with a list of games with FoW:

https://www.giantbomb.com/fog-of-war/3015-14/games/
 
Link to a Dev Blog from League Of Legends about FoW, made by Jaewon Jung:

https://engineering.riotgames.com/news/story-fog-and-war
 
Document about FoW focusing on RTS by Johan Hagelback and Stefan J. Johansson:

http://www.csse.uwa.edu.au/cig08/Proceedings/papers/8052.pdf
 
Document speaking in general about FoW:

http://keithburgun.net/fog-of-war-in-push-the-lane-and-strategy-games-generally/
 
Transform from RGB to RGBA (Add Alpha channel):

https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlsetalpha.html

http://lazyfoo.net/tutorials/SDL/13_alpha_blending/index.php

https://wiki.libsdl.org/SDL_SetTextureAlphaMod
 
GameDev.net, a forum about how to do an efficient FoW:

https://www.gamedev.net/forums/topic/530346-efficient-fog-of-war/
 
Gaussian Blur (Art) at Wikipedia:

https://en.wikipedia.org/wiki/Gaussian_blur

Field Of Vision (not about FoW but interesting)

http://www.roguebasin.com/index.php?title=Field_of_Vision

--------------------------------------------------------------------------------------------------------------------
