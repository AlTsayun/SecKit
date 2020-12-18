//
// Created by RedmiBook on 17.12.2020.
//

#ifndef SECKIT_STYLES_H
#define SECKIT_STYLES_H

//Common
#define STANDARD_PADDING (3)
#define window_client_height_offset (39)
#define window_client_width_offset (16)
#define menu_client_height (20)

//mainWindow
#define main_window_styles (0)
#define main_window_classname L"MainWindowController"
#define main_window_x (0)
#define main_window_y (0)
#define main_window_width (800)
#define main_window_height (600)

#define main_window_absolute_x (100)
#define main_window_absolute_y (100)
#define main_window_absolute_width (main_window_width + window_client_width_offset)
#define main_window_absolute_height (main_window_height + window_client_height_offset + menu_client_height)
#define main_window_title (L"SecKit")

    //leftPanel
    #define left_panel_x (main_window_x)
    #define left_panel_y (main_window_y)
    #define left_panel_width (200)
    #define left_panel_height (main_window_height)

        //searchPanel
        #define search_panel_height (30)
        #define search_panel_width (left_panel_width)
        #define search_panel_x (left_panel_x)
        #define search_panel_y (left_panel_y + left_panel_height - search_panel_height)

            //searchEdit
            #define search_edit_padding STANDARD_PADDING
            #define search_edit_styles (WS_EX_CLIENTEDGE)
            #define search_edit_classname L"Edit"
            #define search_edit_x (search_panel_x + search_edit_padding)
            #define search_edit_y (search_panel_y + search_edit_padding)
            #define search_edit_width (150 - 2*STANDARD_PADDING)
            #define search_edit_height (search_panel_height - 2*search_edit_padding)
            #define search_edit_title L""

            //searchButton
            #define search_button_padding STANDARD_PADDING
            #define search_button_styles (0)
            #define search_button_classname L"Button"
            #define search_button_x (search_panel_x + search_edit_width  + search_button_padding)
            #define search_button_y (search_panel_y + search_button_padding)
            #define search_button_width (search_panel_width - search_edit_width - 2*search_button_padding)
            #define search_button_height (search_panel_height - 2*search_button_padding)
            #define search_button_title L"Search"

        //listLabel
        #define list_label_padding STANDARD_PADDING
        #define list_label_styles (0)
        #define list_label_classname L"Static"
        #define list_label_x (left_panel_x + list_label_padding)
        #define list_label_y (left_panel_y + list_label_padding)
        #define list_label_width (left_panel_width - 2*list_label_padding)
        #define list_label_height (search_panel_height - 2*list_label_padding)
        #define list_label_title L"List"

        //list
        #define list_padding STANDARD_PADDING
        #define list_styles (WS_EX_CLIENTEDGE)
        #define list_classname L"Listbox"
        #define list_x (left_panel_x + list_padding)
        #define list_y (left_panel_y + list_label_height + list_padding)
        #define list_width (left_panel_width - 2*list_padding)
        #define list_height (left_panel_height - list_label_height -  search_panel_height - 2*list_padding)
        #define list_title L""


    //rightPanel
    #define right_panel_x (main_window_x + left_panel_width)
    #define right_panel_y (main_window_y)
    #define right_panel_width (main_window_width - left_panel_width)
    #define right_panel_height (main_window_height)

        //inputPanel
        #define input_panel_width (main_window_width - left_panel_width)
        #define input_panel_height (30)
        #define input_panel_x (right_panel_x)
        #define input_panel_y (right_panel_y + right_panel_height - input_panel_height)

            //inputEdit
            #define input_edit_padding STANDARD_PADDING
            #define input_edit_styles (WS_EX_CLIENTEDGE)
            #define input_edit_classname L"Edit"
            #define input_edit_x (input_panel_x + input_edit_padding)
            #define input_edit_y (input_panel_y + input_edit_padding)
            #define input_edit_width (input_panel_width - 50 - 2*input_edit_padding)
            #define input_edit_height (input_panel_height - 2*input_edit_padding)
            #define input_edit_title L""

            //inputButton
            #define input_button_padding STANDARD_PADDING
            #define input_button_styles (0)
            #define input_button_classname L"Button"
            #define input_button_x (input_panel_x + input_edit_width + input_button_padding)
            #define input_button_y (input_panel_y + input_button_padding)
            #define input_button_width (input_panel_width - input_edit_width - 2*input_button_padding)
            #define input_button_height (input_panel_height - 2*input_button_padding)
            #define input_button_title L"Enter"

        //outputText
        #define output_text_padding STANDARD_PADDING
        #define output_text_styles (WS_EX_CLIENTEDGE)
        #define output_text_classname L"Edit"
        #define output_text_x (right_panel_x + output_text_padding)
        #define output_text_y (right_panel_y + output_text_padding)
        #define output_text_width (right_panel_width - 2*output_text_padding)
        #define output_text_height (right_panel_height - input_panel_height - 2*output_text_padding)
        #define output_text_title L"Hello"

#define main_window_args                     \
        main_window_styles,                  \
        main_window_classname,               \
        main_window_title,                   \
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX /*| WS_MAXIMIZEBOX*/),\
        main_window_absolute_x,              \
        main_window_absolute_y,              \
        main_window_absolute_width,          \
        main_window_absolute_height

#define search_edit_args                     \
        search_edit_styles,                  \
        search_edit_classname,               \
        search_edit_title,                   \
        (WS_VISIBLE | WS_CHILD | WS_TABSTOP),\
        search_edit_x,                       \
        search_edit_y,                       \
        search_edit_width,                   \
        search_edit_height

#define search_button_args                   \
        search_button_styles,                \
        search_button_classname,             \
        search_button_title,                 \
        (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON),\
        search_button_x,                     \
        search_button_y,                     \
        search_button_width,                 \
        search_button_height

#define list_label_args                   \
        list_label_styles,                \
        list_label_classname,             \
        list_label_title,                 \
        (WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_CENTER),\
        list_label_x,                     \
        list_label_y,                     \
        list_label_width,                 \
        list_label_height

#define list_args                   \
        list_styles,                \
        list_classname,             \
        list_title,                 \
        (WS_VSCROLL | WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | LBS_NOTIFY),\
        list_x,                     \
        list_y,                     \
        list_width,                 \
        list_height

#define output_text_args                   \
        output_text_styles,                \
        output_text_classname,             \
        output_text_title,                 \
        (WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL | ES_LEFT | ES_READONLY),\
        output_text_x,                     \
        output_text_y,                     \
        output_text_width,                 \
        output_text_height


#define input_button_args                   \
        input_button_styles,                \
        input_button_classname,             \
        input_button_title,                 \
        (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON),\
        input_button_x,                     \
        input_button_y,                     \
        input_button_width,                 \
        input_button_height

#define input_edit_args                     \
        input_edit_styles,                  \
        input_edit_classname,               \
        input_edit_title,                   \
        (WS_VISIBLE | WS_CHILD | WS_TABSTOP),\
        input_edit_x,                       \
        input_edit_y,                       \
        input_edit_width,                   \
        input_edit_height

#endif //SECKIT_STYLES_H
