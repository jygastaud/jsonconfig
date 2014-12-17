<?php

function jsonconfig_language_handler_validate($def) {
  if (empty($def['language'])) {
    return FALSE;
  }
  return TRUE;
}

function jsonconfig_language_handler_preprocess(&$def) {
  // first we want the defaults from the DB
  $languages = language_list();
  if (isset($languages[$def['language']])) {
    $def += (array) $languages[$def['language']];
  }
  // now we'll add on our own defaults
  $def += array(
    'name' => NULL,
    'native' => NULL,
    'direction' => LANGUAGE_LTR,
    'default' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => '',
    'javascript' => '',
    'enabled' => 0,
  );
}

function jsonconfig_language_handler_create($def) {
  $languages = language_list();
  if (empty($languages[$def['language']])) {
    locale_add_language(
        $def['language'],
        $def['name'],
        $def['native'],
        $def['direction'],
        $def['domain'],
        $def['prefix'],
        $def['enabled'],
        $def['default']
    );
  } else {
    if ($def['default']) {
      variable_set('language_default', (object) $def);
    }
    unset($def['default']);
    db_merge('languages')
        ->key(array('language' => $def['language']))
        ->fields($def)
        ->execute();
  }
}

function jsonconfig_language_handler_refresh($def) {
  jsonconfig_language_handler_create($def);
}

function jsonconfig_language_handler_disable($def) {
  $def['enabled'] = 0;
  jsonconfig_language_handler_create($def);
}

function jsonconfig_language_handler_uninstall($def) {
  db_delete('languages')->condition('language', $def['language'])->execute();
}