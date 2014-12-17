<?php

function jsonconfig_text_format_handler_validate($def) {
  if (!module_exists('filter')) {
    return FALSE;
  }
  if (empty($def['format'])) {
    return FALSE;
  }
  if (empty($def['name'])) {
    return FALSE;
  }
  return TRUE;
}

function jsonconfig_text_format_handler_preprocess(&$def) {
  $def += array(
    'status' => 1,
  );
}

function jsonconfig_text_format_handler_create($def) {
  filter_format_save((object) $def);
}

function jsonconfig_text_format_handler_refresh($def) {
  jsonconfig_text_format_handler_create($def);
}

function jsonconfig_text_format_handler_disable($def) {
  $def['status'] = 0;
  jsonconfig_text_format_handler_create($def);
}
