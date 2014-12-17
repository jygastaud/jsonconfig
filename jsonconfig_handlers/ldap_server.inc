<?php

function jsonconfig_ldap_server_handler_validate($def) {
  if (empty($def['sid'])) {
    return FALSE;
  }
  return TRUE;
}

function jsonconfig_ldap_server_handler_preprocess(&$def) {
  $def += array(
    'status' => 1,
  );
}

function jsonconfig_ldap_server_handler_create($def) {
  db_merge('ldap_server')
    ->fields($def)
    ->key(array('sid' => $def['sid']))
    ->execute();
}

function jsonconfig_ldap_server_handler_refresh($def) {
  jsonconfig_ldap_server_handler_create($def);
}

function jsonconfig_ldap_server_handler_disable($def) {
  $def['status'] = 0;
  jsonconfig_ldap_server_handler_create($def);
}

function jsonconfig_ldap_server_handler_uninstall($def) {
  db_delete('ldap_server')
      ->condition('sid', $def['sid'])
      ->delete();
}