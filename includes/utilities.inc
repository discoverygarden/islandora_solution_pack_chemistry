<?php
/**
 * @file
 * Holds helper functions for islandora_chemistry.
 */

/**
 * Get all lists for table.
 *
 * General function to retrieve the inchikey.
 *
 * @return SelectQuery
 *   The query return.
 */
function islandora_chemistry_get_inchikey_by_id($inchikey) {
  $inchi = db_select('islandora_chemistry_fingerprints')
  ->fields('islandora_chemistry_fingerprints')
  ->condition('id', $inchikey)
  ->execute();
  $data = $inchi->fetchObject();
  return (isset($data->id) ? $data->id : NULL);
}

/**
 * Create a list.
 *
 * @param array $arr_val
 *   Field array as key => value pairs, used in db_insert.
 */
function islandora_chemistry_set_inchikey($arr_val) {
  $data = db_insert('islandora_chemistry_fingerprints')
  ->fields($arr_val)
  ->execute();
  return $data;
}

/**
 * Run fingerprint generation.
 *
 * @param string $filepath
 *   The path to the output temp file.
 *
 * @return number
 *   Return value of the executable.
 */
function islandora_chemistry_run_fingerprint_exec($filepath) {
  $path = drupal_realpath(drupal_get_path('module', 'islandora_chemistry'). '/includes/fingerprint.py');
  $python = variable_get('islandora_chemistry_python', '/usr/bin/python2.7');
  $cmd = "$python $path $filepath";
  $return = 1;
  // This calls a python script to generate the molecular fingerprint
  $fingerprint = array();
  exec($cmd, $fingerprint, $return);
  return $return;
}
