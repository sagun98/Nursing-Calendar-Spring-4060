<?php

/**
 * @file
 * Default theme implementation to display views exposed filters summary.
 *
 * Available variables:
 * - $summary: the array of filters.
 * - $result (not implemented yet): renderable array of $summary.
 * - $path: A result of request_path() function execution.
 */
?>

<div id="exposed-filters" style="margin-top:1em;">

  <?php
  foreach ($summary as $field_name => $filter): ?>
    <span class="exposed-filter-value" >
      <?php
      print $filter['label'];
      $filter_op = ($filter['op'] == 'in' || $filter['op'] == 'or');
      $filter_op = empty($filter['op']) || $filter_op;

      if ($filter_op && count($filter['value']) == 1):
        print ": ";
      else:
        print $filter['opLabel'];
      endif;

      $url = url($path, array('query' => $filter['query_parameters']));
      $classes = implode(' ', $filter['attributes']['class']);
      ?>
      <span class="exposed-filter-selected <?php print $classes; ?>"><?php print $filter['output_value']; ?></span>
      <a class="remove-filter" href="<?php print $url; ?>">X</a>
    </span>
  <?php endforeach; ?>
</div>
