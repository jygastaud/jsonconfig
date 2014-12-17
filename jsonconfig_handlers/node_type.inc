<?php

function jsonconfig_node_type_handler_preprocess(&$def) {
  $def += array(
    'base' => 'node_content',
    'title_label' => 'Title',
    'custom' => TRUE,
    'locked' => TRUE,
  );
}

function jsonconfig_node_type_handler_validate($def) {
  if (empty($def['type'])) {
    return FALSE;
  }
  if (empty($def['name'])) {
    return FALSE;
  }
  return TRUE;
}

function jsonconfig_node_type_handler_create($def) {
  $translate = !empty($def['translatable']) ? !!$def['translatable'] : FALSE;
  node_type_save((object) $def);
  if ($translate) {
    // @todo we should remove this and force them to define it through var.
    variable_set('language_content_type_' . $def['type'], 4);
  }
}

function jsonconfig_node_type_handler_refresh($def) {
  jsonconfig_node_type_handler_create($def);
}

function jsonconfig_node_type_handler_disable($def) {
  $def += array(
    'disabled' => 1,
  );
  node_type_save((object) $def);
}

function jsonconfig_node_type_handler_uninstall($def) {
  node_type_delete($def['type']);
  variable_del('language_content_type_' . $def['type']);
}

function jsonconfig_node_type_handler_list() {
  $node_types = array_keys(node_type_get_types());
  $list = array();
  foreach ($node_types as $node_type) {
    $list[$node_type] = $node_type;
  }
  return $list;
}

function jsonconfig_node_type_handler_export($key) {
  $info = field_info_instances('node', $key);
  foreach ($info as $key => $value) {
    $info[$key] = field_info_field($key);
    unset($info[$key]['storage']);
  }
  return $info;
}
