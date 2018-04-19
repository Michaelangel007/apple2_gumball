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
        const char *name = "gumball.fragment.1.1800";
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

