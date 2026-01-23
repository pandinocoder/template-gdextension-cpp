@tool
extends EditorPlugin

func _enable_plugin() -> void:
	pass

func _disable_plugin() -> void:
	pass


func _enter_tree() -> void:
	print("Initializing GDExtension C++ Build Scripts plugin...")

	_update_file_godot_path()

	print("Initialized GDExtension C++ Build Scripts plugin")


func _exit_tree() -> void:
	print("Removing GDExtension C++ Build Scripts plugin...")

	# Nothing to remove at the moment

	print("Removed GDExtension C++ Build Scripts plugin")

func _update_file_godot_path() -> void:
	var path_to_project := ProjectSettings.globalize_path("res://")
	var path_to_repo := ("%s/.." % [path_to_project]).simplify_path()
	var path_to_godot_path := ("%s/.godot-path" % [path_to_repo]).simplify_path()
	print_debug(
		"Trying to update .godot-path\n\tlocated at: %s\n\tProject: %s\n\tRepository: %s" % [
			path_to_godot_path,
			path_to_project,
			path_to_repo
		]
	)

	var path_to_godot := OS.get_executable_path()
	_update_file(path_to_godot_path, path_to_godot)

func _update_file(p_path_to_file: String, p_content: String) -> void:
	var file_name := p_path_to_file.get_file()
	var fa_target_file := FileAccess.open(p_path_to_file, FileAccess.ModeFlags.WRITE)
	if fa_target_file == null:
		var err_open := FileAccess.get_open_error()
		push_error("Failed to update %s because the file could not be opened\n\tPath: %s\n\tError (%d): %s" % [
			file_name,
			p_path_to_file,
			err_open,
			err_open
		])
	else:
		fa_target_file.store_string(p_content)
		var err_store_string := fa_target_file.get_error()
		if not err_store_string:
			print("[GDXPPBS] Updated %s" % [file_name])
		else:
			push_error("Failed to update %s\n\tPath: %s\n\t Error (%d): %s" % [
				file_name,
				p_path_to_file,
				err_store_string,
				error_string(err_store_string)
			])
		fa_target_file.close()
