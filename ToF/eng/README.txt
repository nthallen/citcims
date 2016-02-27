Engineering Graphs in Matlab
  Setup
    There are three Matlab libraries you will need to install to run the
    engineering plot gui:
      nort: A set of general utility functions
      nort/ne: Functions for engineering plots
      ToFeng: ToF-specific engineeering plots
    Installation involves checking out the libraries from CVS and adding
    them to your Matlab path.
    
    Decide where you want the Matlab libraries to go.
      You probably want to create a base directory for your Matlab
      libraries. This could be a Matlab directory in "My Documents" or
      C:\Matlab. All three of these libraries could then be subdirectories
      of this root directory. On the other hand, you might have all of
      the ToF source code checked out somewhere, so it might make sense
      to leave the ToF-specific engineering plot library where it is.
    
    Download Nort's matlab libraries:
      cvs -d :ext:forge.abcd.harvard.edu:/cvsroot/arp-das co -d nort Matlab/nort
        or
      cvs -d :pserver:anonymous@forge.abcd.harvard.edu:/cvsroot/arp-das login
      cvs -d :pserver:anonymous@forge.abcd.harvard.edu:/cvsroot/arp-das co -d nort Matlab/nort
      
      There are several directories included in this download, but only two that
      should be added to your Matlab path: nort and nort/ne. The others contain
      examples of installation-specific configuration hooks to make other parts
      of the libraries work.

    Download ToF engineering plot directory
      cvs -d :ext:forge.abcd.harvard.edu:/cvsroot/arp-w-cims co -d ToFeng ToF/eng
        Note that this is part of the ToF source hierarchy, so if you already have
        that checked out, cvs update -d should bring it in.
    
    Add nort, nort/ne and ToFeng directories to your Matlab path

    Decide on a root directory for flight/run data
      This directory will contain a subdirectory for each run using the same
      run numbering as under QNX. If you append an 'F' to the name of flight
      runs, then the plots will note that this is flight data.
      
      Each run directory will contain .mat files with all the engineering
      data.
    
    Create ToF_Data_Dir.m (probably in your ToFeng directory):
      function path = ToF_Data_Dir
      % path = ToF_Data_Dir;
      path = 'C:\Data\ToF';

  Setup for a specific run:
    Extract engineering data on QNX:
      extract raw/flight/120504.2 ToFengext
    Copy extract .csv files into ToF_Data_Dir
      I have a script called 'getrun' that I place in the ToF_Data_Dir:
      
        #! /bin/bash
        flt=''
        gse=herc_a
        HomeDir=/home/tof
        Exp=ToF
        for run in $*; do
          if [ $run = "-f" ]; then
            flt=F
          else
            echo $run
            [ -d $run$flt ] || mkdir $run$flt
            scp $gse:$HomeDir/anal/$run/*.csv $run$flt
            [ -n "$flt" ] && scp $gse:$HomeDir/raw/flight/$run/$Exp.log $run$flt/$Exp.log
          fi
        done

      Then 'getrun -f 120504.2' will collect the necessary files. You will need to edit
      this as appropriate.
    
    Convert the .csv files to .mat files:
      In Matlab, cd to the run directory and run csv2mat. You can delete the .csv files
      after the .mat files are created.
      
    Now you have completed the setup for this run. Hereafter, this run's data will be
    readily accessible to the GUI.
    
  Run the GUI:
    ui_ToF
      Select the run from the list on the right. The most recent run is the default.
      Each button in the main area generates a graph. The larger buttons represent
      groups that put multiple graphs on one figure. The grouping is easily
      configurable, so if there are different combinations you'd like to see, let
      me know.
      
      I have added some menu items to the graph displays.
        Zoom: Added before Matlab added their zoom buttons, but still sometimes
          a little easier to use.
        MatchX: After zooming in on an X-axis region in one graph, MatchX will
          zoom all the other graphs in the figure to the same X range.
        Edit: Allows you to further customize the graphs.
        Expand: Allows you to open any of the graphs in it's own figure.
      
  Customization:
    The selection of which data gets displayed in which group is determined
    by the file genui.txt in the telemetry source directory. The program
    that generates the .m files is called 'genui', and it also creates
    the extraction required. The format of genui.txt is documented in
    the usage message for genui, so 'use genui' will explain it.
    
    You will often want to further customize individual graphs. The use of
    lines may be inappropriate on particularly noisy data, for example, or
    the default limits may reflect a transient startup condition, not the
    region of interest. You can edit the .m file for any graph. Most consist
    of a single invocation of my timeplot() function returning vector of
    graphic object handles. You can add statements that alter the graphic
    objects. This is an example from the Harvard Water Vapor instrument:
    
      function phwvsdpp(varargin);
      % phwvsdpp( [...] );
      % SDP P
      h = timeplot({'SD_HP','SD_LP','UVB1_Counts*0.08'}, ...
            'SDP P', ...
            'P', ...
            {'SD\_HP','SD\_LP','UVB1\_Counts'}, ...
            varargin{:} );
      set(h,'LineStyle','none','Marker','.');
      ax = get(h(1),'parent');
      set(ax,'ylim',[0 800]);

    This switches the graphs from lines to symbols and fixes the Y-axis
    limits at [0 800].
    
    Such modifications can be checked back in to CVS to make them available
    to other team members. Subsequent changes to genui.txt will overwrite
    the modifications, but if they are checked in, it is possible to
    reconstruct them. [Ideally I would come up with a system whereby
    modifications would persist...]
    