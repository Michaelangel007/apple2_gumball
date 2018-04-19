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

        if( nArg > 1 )
            name = aArg[1];

        FILE       *in   = fopen( name, "rb" );
        printf( "Filename: %s\n", name );

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

