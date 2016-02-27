%{
  #ifdef SERVER
    
  void write_savelog( const char *s ) {
    FILE *fp;
    fp = fopen( "saverun.log", "a" );
    if ( fp == 0 ) nl_error( 2, "Unable to write to saverun.log" );
    else {
      fprintf( fp, "%s\n", s );
      fclose( fp );
    }
  }
    
  void write_startup( const char *s ) {
    if (s == NULL) {
      if (unlink("Startup.tmas"))
        nl_error(2, "Unable to delete Startup.tmas");
    } else {
      FILE *fp = fopen( "Startup.tmas", "w" );
      if ( fp == 0 ) nl_error( 2, "Unable to write to Startup.tmas" );
      else {
        fprintf( fp, "%s\n", s );
        fclose( fp );
      }
    }
  }
  
  void email_report( int level, const char *file, const char *msg ) {
    FILE *fp;
    fp = fopen( "report.queue", "a" );
    if ( fp == 0 ) nl_error( 2, "Unable to write to report.queue" );
    else {
      if ( file != 0 ) {
        fprintf( fp, "%d [%s] %s\n", level, file, msg );
      } else fprintf( fp, "%d %s\n", level, msg );
      fclose(fp);
    }
  }

  #endif /* SERVER */
%}
&command
  : SaveLog %s (Enter Log Message) * { write_savelog( $2 ); }
  : Startup Define %s (Enter Startup Command) * { write_startup($3); }
  : Startup Clear * { write_startup(NULL); }
  : Email &rpt_level File %w (Enter Filename)
              %s (Enter Message) * {
      email_report( $2, $4, $5 );
    }
  : Email &rpt_level Message %s (Enter Message) * {
      email_report( $2, 0, $4 );
    }
  ;
&rpt_level <int>
  : Report { $0 = 0; }
  : Warning { $0 = 1; }
  : Error { $0 = 2; }
  ;
