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
