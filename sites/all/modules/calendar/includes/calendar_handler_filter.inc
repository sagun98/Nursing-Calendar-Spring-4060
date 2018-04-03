class clicks_handler_filter extends views_handler_filter {
/***************************************************
*     If Something Breaks, Remove what is below     *
****************************************************/

/**
  function admin_summary() { }
  function operator_form() { }
  function query() {
    $table = $this->ensure_my_table();
    $join = new views_join();
    $join->construct('calendar', $this->table_alias, 'nid', 'nid');
    $this->query->ensure_table('calendar', $this->relationship, $join);
    $this->query->add_where($this->options['group'], "USER.CWID", , "=");
 }
 **/
}