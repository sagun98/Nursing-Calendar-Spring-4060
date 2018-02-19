<?php

/**
 * @file
 * Provide views data for views_exposed_filters_summary.module.
 */

/**
 * Implements hook_views_data_alter().
 */
function views_exposed_filters_summary_views_data_alter(&$data) {
  $data['views_exposed_filters_summary'] = array(
    'table' => array(
      'group' => t('Views exposed filters summary'),
      'join' => array('#global' => array()),
    ),
  );
  $data['views_exposed_filters_summary']['exposed_filters_summary'] = array(
    'title' => t('Exposed filters summary'),
    'help' => t('Shows result summary, for example the items per page.'),
    'area' => array(
      'handler' => 'ViewsExposedFiltersSummaryHandlerAreaExposedFiltersSummary',
    ),
  );
}
