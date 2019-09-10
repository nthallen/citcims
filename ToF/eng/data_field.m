classdef data_field < handle
  % data_field represents two text objects,
  % a label and the value display, and the corresponding
  % data stream
  properties(GetAccess = public)
    flds % The parent data_fields object
    rec_name
    var_name
    fmt
    lbl_name
    lbl
    txt
    lbl_width
    txt_width
    fld_height
  end
  methods
    function df = data_field(flds, rec_name, var_name, fmt, signed)
      if nargin < 5
        signed = false;
      end
      df.flds = flds;
      df.fmt = fmt;
      df.rec_name = rec_name;
      df.var_name = var_name;
      df.lbl_name = [rec_name '_lbl'];
      lbltxt = [var_name ':'];
      df.lbl = uicontrol(flds.fig, ...
        'Style', 'text', 'String', lbltxt, ...
        'HorizontalAlignment', 'left', ...
        'BackgroundColor', flds.figbgcolor, ...
        'FontWeight', 'bold', ...
        'tag', df.lbl_name, ...
        'uicontextmenu', flds.dfuicontextmenu, ...
        'userdata', df);
      df.lbl_width = df.lbl.Extent(3);
      str = df.txt_convert(0);
      if signed
        str = [ '-' str ];
      end
      df.txt = uicontrol(flds.fig, ...
        'Style', 'text', 'String', str, ...
        'HorizontalAlignment', 'right', ...
        'BackgroundColor', [1 1 1], ...
        'FontName', flds.opts.txt_font, ...
        'FontSize', flds.opts.txt_fontsize, ...
        'tag', df.var_name);
      df.txt_width = df.txt.Extent(3);
      df.fld_height = max(df.lbl.Position(4), df.txt.Position(4));
    end
    
    function str = txt_convert(obj, val)
      if isnumeric(obj.fmt)
        str = num2str(val,obj.fmt);
      else
        str = sprintf(obj.fmt,val);
      end
    end
  end
end
