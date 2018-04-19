Revised: April 19, 2018

# Gumball Easter Eggs

# Table of Contents

* Introduction
* Pre-requisites
* In-game Hints
* Long Lost Gumball Source Code!
  * Fragment GB.1.a
  * Fragment GB.1.b
  * Fragment GB.1.c
  * Fragment GB.1.d
  * Fragment GB.1.e
  * Fragment GB.1.f
  * Dump Listing
  * Fragment GB.1.All
  * Fragment GB.2
  * Dump Symbols
  * Fragment GB.2.All
  * Fragment GB.3.a
  * Fragmnet GB.3.b
  * Fragment GB.3.All (TODO)
* Hints Revisited
* Hall of Fame
  * Credits
* Job Titles
* Secret in-game end message
* Appendix A: Sector Interleave


# Introduction

I don't know what it is about Apple 2 games
but I love using a sector editor viewing
every track and sector for easter eggs. I guess
it is the thrill of (re)discovering something
that hasn't been seen in 20 - 40 years that
has been seen only by the author.

Today we'll discover some easter eggs hidden
in Br0derbund's "Gumball". A regular player 
will _never_ see these since they are never shown. 
They are "remnants" left over from the build process.
And the only way to view them is to either

* view memory
* view the disk contents

We'll be using a "cracked" copy -- specifically
games that have been converted over to a standard
Track/Sector format.  We'll also be using a sector
editor -- "Copy ][ Plus" is the standard 'go to too'
that we'll use.



# Pre-requisites

There are few different cracked versions out there.

We'll use these disks:

* [gumball_fixed](ftp://ftp.apple.asimov.net/pub/apple_II/images/games/action/gumball-fixed.zip)
* [Gumball (4am & san inc crack)](ftp://ftp.apple.asimov.net/pub/apple_II/images/games/)

4am's version is the most "pristine" -- he only
removes the copy protection scheme and keeps
_everything_ else in-tact.  We even have his
cracking notes to follow along and verify!

I'll also be using another version since it
will be curious if other crackers kept everything
or not.



# In-game Hints

4am, T02SB

We have a strange 24 character string:

```
1B:_____ ________ __FIG YRJMYR<FF>
```

Instead of C's ASCIIZ we have ASCIIFF where FF is the end sentinel.

This is actually in-game hint #4 (using a subtituion chipher)

```YOU RETIRE```

4am has documented all of those in his notes:

* "Gumball (4am & san inc crack).txt"

The remaining hints have a lookup table on T12/S4/@AA

```
    $FB2
    $FD4
    $FF6
    $1014
```

Note: The strings are not null terminated but $FF terminated.

| Hint          | Location  | Memory |
|:-------------:|:---------:|:------:|
| `RBJRY JSYRR` | T12S4 @B2 | $0FB2  |
| `VRJJRY ZIAR` | T12S4 @D4 | $0FD4  |
| `ESRB`        | T12SB @F6 | $0FF6  |
| `FIG YRJMYR`  | T12SB @14 | $1014  |

For some reason the last hint is duplicated on T02SB which 
is located in memory @ $101B ?


And now for something completely different ...



# Long Lost Gumball Source Code!

No, this isn't the _entire_ source code -- only fragments of it.

Still let's see what treasure we can "mine" by "spelunking."


## Fragment GB.1.a

I'm call this Source Code Fragment `GB.1._x_`

Since we have two disk images:

* I'll prefix `4am's` DSK image with `4am`, and
* I'll prefix `Gumball Fixed` DSK image with 'Fix'.

Here is the track/sector infor for the first fragment.

* 4am, T3S0
* Fix, T2S0

The first fragement is an assembler header block!

```asm
;
;
;
;
;
; --------------------------------
; <                              <
; <           "BLOCK2"           <
; <                              <
; <    TABLES AND BLOCK SHAPES   <
; <                              <
; <         ROBER
```

It is continued on:

4am, T03S7
Fix, T02S7

```asm
;                T COOK          <
; <                              <
; --------------------------------
;
;
;
;
;
;
; GUMBALL TITLE BLOCK
;
;
;
;
;
; GUMBALL       
d 280000000
d 0000000000000000
d 0000000000000000
d 0000000000000000
d 00000A2800000000
d 0
```

**NOTE:** 

* I'm leaving out the control characters,
* It looks like $13 is used to represent a TAB ($09) char?


This is continued on either T03S4, T03SC, or T03SE.
But which is one is correct?


## Fragment GB.1.b

4am, T03S4
Fix, T02S4

Let's padd the front with space(s) to align
the text.

```asm
   F7F837F8360FF81  (1) @00
d 000A28703F80E67F  (2) @11
d FC0FE0FFF83FFE7F  (3) @25
d F37F787F7F0FFE5F  (4) @39
d FF077F8360FF8100  (5) @4D
d 0A28703F80667FFC  (6) @61
...
d 7F0360FF81000A28
```

Now we're going to "cheat" -- that is: _"Work smarter not harder"_

Searching for `FC 0F E0 FF` the raw bytes on line 3 can be found at:

* 4am, T7S5 @4C
* Fix, T5S1 @4C

From this we can deduce three, no four, no five, things:

* We know the first digit should be `7`,
* That rules out Sectors $4 and $E, leaving Sector $C,
* We _must_ verify our assumptions,
* We can start to see the sector interleaving table,
* Even if we _weren't_ able to find the raw hex bytes on disk we
could have assumed that Sector $E followed from Sector $7 by
inspection and noticing the run of zeroes.


## Fragment GB.1.c

Making a table of what we have so far:

| Sector | Mem |
|:-:|:-----:|
| 0 | $1800 |
| 7 | $1900 |
| : | :     |
| C | $?000 |
| 4 | $?100 |




4am, T03SC
Fix, T02SC

```asm
       F7F7F3F603C   (1) @00
d FF07307E7F01FF07   (2) @0D
d 70FF01000A28707F   (3) @21
d 000000781F607F70   (4) @35
d FF7F7F7F3FF0FC7F   (5) @49
...
d 7FF773FB87E7F077  (13) @E9
d 7                 (14) @FD
``` 

Without visually inspecting these HGR bytes
it would look like T03S4 is the contination due
to each row being 16 characters.

Why?

Since S3S7 ends with 1 character that means the next
row will only have 15 characters. At first glance T03S4
would fit the bill.

However, we must always _verify_ our assumptions.

That's why we did the `Hex Search` earlier and found
the _actual_ answer was T03SC and *not* our _expected_ T03S4.

An exercise for the reader: "Rip" the sprites from the 
startup demo and re-construct the actuall assembly source.


## Fragment GB.1.d

Sector $E looks like the continuation of S0.

```asm
   000000000000000   (1) @00
d 0000000000000000   (2) @11
d 0000000000000000   (3) @25
d 000A280000000000   (4) @39
d 0000000000000000   (5) @4D
d 0000000000000000   (6) @61
d 0000000000000000   (7) @75
d 0A28000000000000   (8) @89
d 0000000000000000   (9) @9D
d 0000000000000000  (10) @B1
d 0000000000000000  (11) @C5
d 2800007E0300000F  (12) @D9
d 4007007003007C00  (13) @ED
```


| Sector | Mem |
|:-:|:-----:|
| 0 | $1800 |
| 7 | $1900 |
| E | $1A00 |
| : | :     |
| C | $?000 |
| 4 | $?100 |


## Fragment GB.1.e

From the above analysis we have enough to put together
a sector interleaving table.

|Logical|Physical|
|:-----:|:------:|
| 0 | 0 |
| 1 | 7 |
| 2 | E |
| 3 | 6 |
| 4 | D | 
| 5 | 5 |
| 6 | C |
| 7 | 4 |
| 8 | B |
| 9 | 3 |
| A | A |
| B | 2 |
| C | 9 |
| D | 1 |
| E | 8 |
| F | F |

Let's inspect Sector $6

4am, T03S6
Fix, T02S6

```asm
d 007F0F0000000000   (1) @01
d 7001000F00000A28   (2) @15
:
d 07787C0300660      (13) @F1
```


## Fragment GB.1.f

4am, T03SD
Fix, T02SD

```asm
               730   (1) @00
d 7E00000A2800CF7F   (2) @05
:
d 0A2860FF7         (13) @F5
```


## Fragment GB.1.All

Here is the the complete sector and memory list for Fragment 1:

| Sector | Mem |
|:-:|:-----:|
| 0 | $1800 |
| 7 | $1900 |
| E | $1A00 |
| 6 | $1B00 |
| D | $1C00 |
| 5 | $1D00 |
| C | $1E00 |
| 4 | $1F00 |

A complete _half of track's worth of data_ is source code!?

The simplest way to save this non-linear data into a linear format
is too boot the game up and inspect memory at the title sequence.

From AppleWin:

* `bsave "gumball.fragment.1.1800",1800:1FFF`


## Dump Listing

Here's a C program, [dump_list.c](dump_list.c), to dump the fragment:

```c
// Includes
    #include <stdio.h>  // printf()
    #include <stdlib.h> // malloc()

// Util

    size_t FileSize( FILE *file )
    {
        if( !file )
            return 0;

        // Yes, this is insecure
        // and we should use stat()
        // but that isn't available under Windows
        fseek( file, 0, SEEK_END );
        size_t size = ftell( file );
        fseek( file, 0, SEEK_SET );

        return size;
    }

// Main

    int main()
    {
        const char *name = "gumball.fragment.1.1800";
        FILE       *in   = fopen( name, "rb" );

        if( in )
        {
            size_t size = FileSize( in );

//printf( "Size: %lld\n", size );

            if( size )
            {
                char *buffer = (char*) malloc( size );

                int  i;
                int  n = (int) size;
                char c;

                size_t read = fread( buffer, 1, size, in );

                if( read != size )
                    printf( "ERROR: Only read %lld / %lld bytes\n", read, size );

                for( i = 0; i < n; i++ )
                {
                    c = buffer[ i ] & 0x7F;

                    if( c == 0x0D )
                    {
                        printf( "\n" );

                        c = buffer[ ++i ];
                        if( (c == 0x13) || (c == 0x0B) )
                            printf( "\t" );
                        else
                            printf( " " );
                    }
                    else
                    if( c < 0x20 )
                        ;
                    else
                        printf( "%c", c );
                }

                free( buffer );
            }

            fclose( in );
        }
        else
            printf( "ERROR: Couldn't open: '%s'\n", name );

        return 0;
    }
```

And finally, our moment of truth!

```asm
;
 ;
 ;
 ;
 ;
 ; --------------------------------
 ; |                              |
 ; |           "BLOCK2"           |
 ; |                              |
 ; |    TABLES AND BLOCK SHAPES   |
 ; |                              |
 ; |         ROBERT COOK          |
 ; |                              |
 ; --------------------------------
 ;
 ;
 ;
 ;
 ;
 ;
 ; GUMBALL TITLE BLOCK
 ;
 ;
 ;
 ;
 ;
 GUMB    :
	d 28000000
	d 0000000000000000
	d 0000000000000000
	d 0000000000000000
	d 00000A2800000000
	d 0000000000000000
	d 0000000000000000
	d 0000000000000000
	d 000A280000000000
	d 0000000000000000
	d 0000000000000000
	d 0000000000000000
	d 0A28000000000000
	d 0000000000000000
	d 0000000000000000
	d 000000000000000A
	d 2800007E0300000F
	d 4007007003007C00
	d 007F0F0000000000
	d 7001000F00000A28
	d 00607F1F00601F60
	d 0F807C0F007F0370
	d 7F7F00401F00007C
	d 03603F00000A2800
	d 387E3F00203E301E
	d 007E3F607F07787F
	d 7F03707F00006407
	d 70BF80000A28008E
	d 7E6700303E301E80
	d 737F307E87FC7F7F
	d 07787C0300660730
	d 7E00000A2800CF7F
	d 6700703FF83F40F3
	d 7FB87E0FCC7F7F87
	d 787C07007E87307E
	d 00000A2840FF7F7F
	d 00F83FF83FE07F7F
	d 797F1F4C7F7F0F78
	d 7F0F007E87707F80
	d 000A28407F7F7F00
	d 983FF83FE0797FFD
	d 7F1FFC7F7F0F787F
	d 1F007287707F8000
	d 0A2860FF7F3F0098
	d 3F703FE0797F7F7F
	d 3F7C7F7F0F707F3F
	d 007287707F01000A
	d 28607F871F00183F
	d 707F607C7F7F7F3F
	d 789FFE0F407F7F00
	d F30770FF01000A28
	d 70FF810000781F60
	d 7F607C7F7F7F3F40
	d 3FFC87607F7F80FF
	d 0770FF01000A2870
	d FF800000781F607F
	d 70FF7F7F7F3F603C
	d FF07307E7F01FF07
	d 70FF01000A28707F
	d 000000781F607F70
	d FF7F7F7F3FF0FC7F
	d 83187F7F81FF8360
	d 7F01000A28703F80
	d 7007780FE0FF70FF
	d 7E7F773FB07E7F81
	d 9C7F7F03FF83607F
	d 01000A28703F807C
	d 3F780FE0FF707F7E
	d 7F773FB87E7F077C
	d 7F7F837F8360FF81
	d 000A28703F80E67F
	d FC0FE0FFF83FFE7F
	d F37F787F7F0FFE5F
	d FF077F8360FF8100
	d 0A28703F80667FFC
	d 0F407FF83F7C7F63
	d 7F785F7F0FFF1F7F
	d 877F0360FF81000A
	d 28707F007E7FFC0F
	d 407FF83F787F617F
	d 781F7C1FFF0FFF0F
	d 7F0360FF81000A28
```

## Fragment GB.2

On Track $08 we we find more snippets of assembly source:

Fragment GB.2a, T08S4

```
    +,ANDPIC  V,BALLINDHW,BALLINDLZ,BMINDH  ],BMIND
```

This looks like a symbol table.  

If we boot the game and again inspect memory at the title
sequence we see that this is loaded into memory at $8400.
We are interested in the snippet from $849a onwards.

The format of the symbol table is this in C:


```c
struct
{
    uint8_t  name[8];
    uint16_t address;
}
```

The first two letters at $849A and $849B got
over-written with zeroes. We can over-write
these 2 end bytes of graphics data with underscores
(`_`) $5F:

* 849A:5F
* 849B:5F
* `bsave "gumball.fragment.2.849a",849a:87FF`



## Dump Symobls

We can modify our `dump_list` converting it to
[dump_sym.c](dump_sym.c) to dump the symbol table:


```c
// Includes
    #include <stdio.h>  // printf()
    #include <stdlib.h> // malloc()

// Util

    size_t FileSize( FILE *file )
    {
        if( !file )
            return 0;

        // Yes, this is insecure
        // and we should use stat()
        // but that isn't available under Windows
        fseek( file, 0, SEEK_END );
        size_t size = ftell( file );
        fseek( file, 0, SEEK_SET );

        return size;
    }

// Main

    int main( const int nArg, const char *aArg[] )
    {
        const char *name = "gumball.fragment.2.849a";
        FILE       *in   = fopen( name, "rb" );

        if( nArg > 1 )
            name = aArg[1];       

        if( in )
        {
            size_t size = FileSize( in );

//printf( "Size: %lld\n", size );

            if( size )
            {
                char *buffer = (char*) malloc( size );

                int  src;
                int  len = (int) size;

                size_t read = fread( buffer, 1, size, in );

                char name[ 9 ];

                if( read != size )
                    printf( "ERROR: Only read %lld / %lld bytes\n", read, size );

    
                for( src = 0; src < len; )
                {
                    int dst;
                    for( dst = 0; dst < 8; dst++ )
                        name[ dst ] = buffer[ src + dst ];
                    name[ 8 ] = 0;

                    printf(
                        "%s EQU $%02X%02X\n"
                        , name
                        , (buffer[ src + 9 ] & 0xFF)
                        , (buffer[ src + 8 ] & 0xFF)
                     );

                    src += 10;
                }

                free( buffer );
            }

            fclose( in );
        }
        else
            printf( "ERROR: Couldn't open: '%s'\n", name );

        return 0;
    }
```

## Fragment GB.2.All

Lo and behold!

```asm
__OB     EQU $084C
DROP1    EQU $087B
DROP2    EQU $0892
BALLDOOR EQU $08CF
RASEPOLE EQU $08E3
MAKECRS1 EQU $0900
SHOWGUMB EQU $0922
COPYRITE EQU $0948
PRELIM   EQU $0978
MAKECRS2 EQU $09A8
SHOWROB  EQU $09CE
SHOWDOUG EQU $09F4
GUMBDR   EQU $0A30
CROSSDR  EQU $0A6B
PLOT     EQU $0AB2
POLEUP   EQU $0AFC
OPENBALL EQU $0B1B
BALLDRP1 EQU $0B5D
CHUNKPLT EQU $0BA5
BALLSET  EQU $0BC5
BALLDRP2 EQU $0BEC
BBPLOT   EQU $0C3D
EEPLOT   EQU $0C63
ANPLOT   EQU $0C89
PRPLOT   EQU $0CBD
BBUNPLOT EQU $0CE3
EEUNPLOT EQU $0D07
ANUNPLOT EQU $0D2D
PRUNPLOT EQU $0D58
ROTKNOB  EQU $0D7E
PAUSE    EQU $0DD5
LPAUSE   EQU $0E15
SCRFLIP  EQU $0E1F
SCRCLR   EQU $0E33
SCRTRANS EQU $0E4C
TRANSOUT EQU $0E6E
TRANSIN  EQU $0E90
BLOCK1   EQU $0EB2
BLOCK2   EQU $0EE6
BLOCK3   EQU $0F52
B3LOOP   EQU $0F54
MAIN     EQU $0F9D
STARTUP  EQU $0FD3
YLO      EQU $6000
YHI      EQU $60C8
KNOBIND  EQU $6190
KNOB1    EQU $619A
KNOB2    EQU $62AE
KNOB3    EQU $63C2
KNOB4    EQU $64D6
KNOB5    EQU $65EA
BB       EQU $66FE
BRODB    EQU $68C5
EE       EQU $68C6
ELTE     EQU $6A2D
PRE      EQU $6A2E
PRES     EQU $6B0D
NEWY1    EQU $6B0E
NEWY2    EQU $6B6B
NEWY3    EQU $6BCB
NEWY4    EQU $6C0B
AND      EQU $6C2B
ANDPIC   EQU $6C56
BALLINDH EQU $6C57
BALLINDL EQU $6C5A
BMINDH   EQU $6C5D
BMINDL   EQU $6C60
BALL1    EQU $6C63
BALLM    EQU $6C99
OBALLIND EQU $6CCF
OBALL1   EQU $6CD9
OBALL2   EQU $6D60
OBALL3   EQU $6DE7
OBALL4   EQU $6E6E
OBALL5   EQU $6EF5
PATH1    EQU $6F7C
PATH2    EQU $6F9A
GUMCHUNK EQU $6FDF
BALL2    EQU $7033
BALL3    EQU $7069
WHTMASK  EQU $709F
BYTET    EQU $70D5
BLOCKPOS EQU $71D9
DOTS1    EQU $730A
DOTS2    EQU $7311
GUMB     EQU $7318
GUMBR    EQU $006B
```


4am, Track $8

| Sector | Mem |
|:-:|:-----:|
| D | $8400 |
| 5 | $8500 |
| C | $8600 |
| 4 | $8700 |

Fragment GB.2.a, T08S4
Fragment GB.2.b, T08S5
Fragment GB.2.c, T08SC
Fragment GB.2.d, T08SD



## Fragment GB.3a

There is 3rd fragment on disk!

* 4am, T13S0
* Fix, T11S0

```
;
;
;
;
;   -----------------------------
; <                              <
; <           "BLOCK3"           <
; <                              <
; <    TABLES AND BLOCK SHAPES   <
; <                              <
; <         ROBE
```

## Fragment GB.3.b

It is continued on 4am, T13S7

```
                RT COOK          <
; <                              <
;   -----------------------------
```


Using our sector interleave table:

|:Sector:| Order |
| 0 |0 | 
| 7 |1 | 
| E |2 | 
| 6 |3 | 
| D |4 |  
| 5 |5 | 
| C |6 | 
| 4 |7 | 

I still need to track down where this is loaded into memory.

To save this we have three choices:

* Play the game, and inspect memory where this is loaded which is time consuming,
* Manually save this "piece-meal" from `Copy ][+` which is still time consuming, or
* We make a "temp copy" of the game and and over-write the previous fragment 1 with fragment 3.

Let's do the latter:

* Read: T13S0, Write: T3S0
* Read: T13S4, Write: T3S4
* Read: T13S5, Write: T3S5
* Read: T13S6, Write: T3S6
* Read: T13S7, Write: T3S7
* Read: T13SC, Write: T3SC
* Read: T13SD, Write: T3SD
* Read: T13SE, Write: T3SE

Back in AppleWin

* `bsave "Gumball.fragment.3.1800",1800:1FFF`




## Fragment GB.3.All

Using our [dump_list.c](dump_list.c) program:

```asm
;
 ;
 ;
 ;
 ;
 ; --------------------------------
 ; |                              |
 ; |           "BLOCK3"           |
 ; |                              |
 ; |    TABLES AND BLOCK SHAPES   |
 ; |                              |
 ; |         ROBERT COOK          |
 ; |                              |
 ; --------------------------------
 ;
 ;
 [ $5800
 ;
 ;
 ;
 ;
 ;
 ; CROWN PICTURE
 ;
 ;
 ;
 ;
 ;
 CROWNS  :
	d 624E624D624C644B
	d 644C644D644E664D
	d 664C664B664A684A
	d 684B684C6A4C6A4B
	d 6A4A6A496C496C4A
	d 6C4B6E4B6E4A6E49
	d 7049704A704B724B
	d 724A72497449744A
	d 744B764B764A7649
	d 7849784A784B784C
	d 7A4C7A4B7A4A7C4A
	d 7C4B7C4C7C4D7E4E
	d 7E4D7E4C7E4B804C
	d 804D804E824F824E
	d 844E824D824C844D
	d 824B844C864C864B
	d 844B844A864A8649
	d 8449824982488448
	d 8447824782468446
	d 8445824580458044
	d 8244824380438042
	d 8242824180417E41
	d 7E408040803F7E3F
	d 7E3E803E803D7E3D
	d 7C3D7C3C7C3B7E3C
	d 7E3B7E3A7E398038
	d 8039803A823A8239
	d 8238823784378438
	d 8439863986388637
	d 8636883688378838
	d 8A388A378A368C36
	d 8C378C388E388E37
	d 8E36903690379038
	d 9239923892379236
	d 943794389439963A
	d 9639963896379838
	d 9839983A9A399A3A
	d 9C3B9A3B9C3C9C3D
	d 9A3C9A3D983D983E
	d 9A3E9A3F983F9840
	d 9A409A4198419641
	d 9642984298439643
	d 9644984498459645
	d 9445944696469647
	d 9447944896489649
	d 94499249924A944A
	d 924B924C944B964B
	d 944C964C944D944E
	d 964F964E964D984C
	d 984D984E9A4E9A4D
	d 9A4C9A4B9C4A9C4B
	d 9C4C9C4D9E4C9E4B
	d 9E4AA049A04AA04B
	d A04CA24BA24AA249
	d A449A44AA44BA64B
	d A64AA649A849A84A
	d A84BAA4BAA4AAA49
	d AC49AC4AAC4BAE4C
	d AE4BAE4AAE49B04A
	d B04BB04CB24AB24B
	d B24CB24DB44EB44D
	d B44CB44BB64EB64D
	d B84FB84EB64CB84D
	d BA4EBA4DB84CBA4C
	d BC4CBC4BBA4BB84B
	d BA4ABC4ABC49BA49
	d B849B848BA48BA47
	d B847B846BA46BA45
	d B845B645B644B844
	d B843B643B642B842
	d B841B641B441B440
	d B640B63FB43FB43E
	d B63EB63DB43DB23D
	d B23CB43CB43BB23B
	d B23AB43AB439B239
	d B238B039B237B236
	d B036B037B038AE38
	d AE37AE36AC36AC37
	d AC38AA38AA37AA36
	d A836A837A838A638
	d A637A636A436A437
	d A4
```



# Hints revisted

4am ,T0DS3 has this message:

```
    PRESS CTRL-Z DURING THE CARTOONS
```

# Hall of Fame

T11S2 has the High Score headers

```
----------------------------------------

     ALL TIME CHAMPSIONS OF GUMBALL     

    #    INITIALS    SCORE     LEVEL
   ---  ----------  -------   -------
```

## Credits

The end of the credits is:

4am, T11S3, @ 00

```
. STAUB
JIM KASSENBROCK    U.C.B.C.


AND ALL OF THE AMAZING PEOPLE AT

              BR0DERBUND
```

The first half of the credits is the following sector:


4am, T11S4, @BE

```
        >>>>>>>> CREDITS <<<<<<<<

THE FOLLOWING PEOPLE HAD SOMETH
```

4am, T11SB @00

```
THING TO DO  WITH 

``` 



# Job Titles

T11SC

```
WORKER
FOREMAN
SUPERVISOR
MANAGER
VICE PRESIDEN
```



# Secret in-game end message

We see another hint:

4am, T12S7 @87

```
              DOUBLE HELIX
```

Here we see the congratulations screen T12S7 @DD ...

```
AHA!  YOU MADE IT!
EITHER YOU AR
```

... continued on T12SE ...

```
E AN EXCELLENT GAME-PLAYER
OR (GAH!) PROGRAM-BREAKER!
YOU ARE CERTAINLY ONE OF THE PEOPLE
THAT WILL EVER SEE THIS SCREEN.

THIS IS NOT THE END, THOUGH.

IN ANOTHER BR0DERBUND PRODUCT
TYPE 'Z0DWARE' FOR MORE PUZZLES.

HAVE FUN!  BYE!!
________________
```

(I've displayed the spaces with underscores for the last line.)


... and concluded on T12S6

```
      R.A.C.
```

I discovered this back in the mid 80's.  I never documented
since I figured that if _I_ had used a sector editor to 
see it, **surely** someone else would have.

Who knew that it was never publically announced.

DOH!

Oh well, it's been 20 years of fun knowing about these hidden treasures!


# Appendix A: Sector Interleave

Here is a translation table to map logical sectors to physical sectors and vice versa.

NOTE: Copy ][+ reads physical sectors.

|Logical|Physical|
|:-----:|:------:|
| 0 | 0 |
| 1 | 7 |
| 2 | E |
| 3 | 6 |
| 4 | D | 
| 5 | 5 |
| 6 | C |
| 7 | 4 |
| 8 | B |
| 9 | 3 |
| A | A |
| B | 2 |
| C | 9 |
| D | 1 |
| E | 8 |
| F | F |


Revisions

* Sept 24, 2017
* April 18, 2018
* April 19, 2018

