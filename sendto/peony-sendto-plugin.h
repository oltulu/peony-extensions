/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/* 
 * Copyright (C) 2004 Roberto Majadas
 * Copyright (C) 2009 Bastien Nocera <hadess@hadess.net>
 * Copyright (C) 2017, Tianjin KYLIN Information Technology Co., Ltd.
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more av.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301  USA.
 *
 * Authors:  Roberto Majadas <roberto.majadas@openshine.com>
 *           Bastien Nocera <hadess@hadess.net>
 * Modified by : liupeng <liupeng@kylinos.cn>
 */

#ifndef _PEONY_SENDTO_PLUGIN_H_
#define _PEONY_SENDTO_PLUGIN_H_

#include <gmodule.h>
#include <gtk/gtk.h>

/**
 * SECTION:peony-sendto-plugin
 * @short_description: peony-sento plug-in
 * @stability: Stable
 * @include: bluetooth-plugin.h
 *
 * Plug-ins can be used to extend peony-sendto.
 **/

typedef struct _NstPluginInfo NstPluginInfo;
typedef struct _NstPlugin NstPlugin;

/**
 * NstPluginCapabilities:
 * @PEONY_CAPS_NONE: No capabilities
 * @PEONY_CAPS_SEND_DIRECTORIES: The plugin can send whole directories without compression
 * @PEONY_CAPS_SEND_IMAGES: The plugin only sends images which could be resized
 *
 * Capabilities of the plugin.
 **/
typedef enum {
	PEONY_CAPS_NONE = 0,
	PEONY_CAPS_SEND_DIRECTORIES = 1 << 0,
	PEONY_CAPS_SEND_IMAGES = 1 << 1,
} NstPluginCapabilities;

/**
 * NstPluginInfo:
 * @icon: The icon name for the plugin selection drop-down
 * @id: A unique ID representing the plugin
 * @description: The label used in the plugin selection drop-down
 * @gettext_package: The domain to use to translate the description, %NULL if the plugin is part of peony-sendto
 * @capabilities: a bitmask of #NstPluginCapabilities
 * @init: Check for dependencies, and return %FALSE if dependencies such as programs are missing.
 * @get_contacts_widget: Return the contact widget, the widget to select the destination of the files
 * @validate_destination: Validate whether the destination can receive the file. This callback is optional.
 * @send_files: Actually send the files to the selected destination. The file list is a #GList of URI strings.
 * @destroy: Free all the resources used by the plugin.
 *
 * A structure representing a peony-sendto plugin. You should also call NST_INIT_PLUGIN() on the plugin structure to export it.
 **/
struct _NstPluginInfo
{
	gchar                             *icon;
	gchar                             *id;
	gchar                             *description;
	gchar                             *gettext_package;
	NstPluginCapabilities              capabilities;
	gboolean (*init)                  (NstPlugin *plugin);
	GtkWidget* (*get_contacts_widget) (NstPlugin *plugin);
	gboolean (*validate_destination)  (NstPlugin *plugin, GtkWidget *contact_widget, char **error);
	gboolean (*send_files)            (NstPlugin *plugin,
					   GtkWidget *contact_widget,
					   GList *file_list);
	gboolean (*destroy)               (NstPlugin *plugin) ;
};

/**
 * NstPlugin:
 * @module: the #GModule for the opened shared library
 * @info: a #NstPluginInfo structure
 *
 * A structure as used in peony-sendto.
 **/
struct _NstPlugin
{
	GModule *module;
	NstPluginInfo *info;
};

/**
 * NST_INIT_PLUGIN:
 * @plugininfo: a #NstPluginInfo structure representing the plugin
 *
 * Call this on an #NstPluginInfo structure to make it available to peony-sendto.
 **/
# define NST_INIT_PLUGIN(plugininfo)					\
	gboolean nst_init_plugin(NstPlugin *plugin);			\
        G_MODULE_EXPORT gboolean nst_init_plugin(NstPlugin *plugin) {	\
		plugin->info = &(plugininfo);				\
                return TRUE;						\
        }	

#endif /* _PEONY_SENDTO_PLUGIN_H_ */

