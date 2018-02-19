<?php

/**
 * @file
 * Contains ViewsExposedFiltersSummaryHandlerAreaExposedFiltersSummary.
 */

/**
 * ViewsExposedFiltersSummaryHandlerAreaExposedFiltersSummary class.
 */
class ViewsExposedFiltersSummaryHandlerAreaExposedFiltersSummary extends views_handler_area {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['filters'] = array('default' => NULL);
    $options['show_operators'] = array('default' => NULL);
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $this->view->init_handlers();

    $filter_options = array();
    foreach ($this->view->filter as $id => $handler) {
      if ($handler->is_exposed()) {
        $filter_options[$id] = $handler->ui_name();
      }
    }
    $form['filters'] = array(
      '#type' => 'select',
      '#title' => t('Filters'),
      '#multiple' => TRUE,
      '#options' => $filter_options,
      '#default_value' => $this->options['filters'],
      '#description' => t('Choose the filters, if none are selected, all will be used'),
      '#process' => array('form_process_select'),
    );

    $form['show_operators'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display operators'),
      '#default_value' => $this->options['show_operators'],
      '#description' => t('If checked, the operators will be displayed, rather than just foo : bar'),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function render($empty = FALSE) {
    $summary = $this->viewsExposedFiltersSummary($this->view);
    return theme('views_exposed_filters_summary_results', array('summary' => $summary));
  }

  /**
   * Returns an array of summary information.
   *
   * @param \view $view
   *   Views object.
   *
   * @return array
   *   An array of summary data.
   */
  protected function viewsExposedFiltersSummary(view $view) {
    $operators = array(
      'allwords' => t('Contains all words from'),
      'or' => t('One of'),
      'and' => t('All of'),
      'not' => t('Not in'),
      'word' => t('Contains a word from'),
      'in'  => t('In'),
      'not in' => t('Not In'),
    );
    // First we get all filters in a view in array $filters_summary.
    $filters_summary = array();

    $selected_filters = !empty($this->options['filters']) ? $this->options['filters'] : array();
    $show_operators = $this->options['show_operators'];
    $names = array();
    foreach ($view->filter as $filter_key => $filter) {

      // Deal only with exposed filters.
      if ($filter->options['exposed'] === FALSE) {
        continue;
      }

      $field = $filter->field;
      $name = $field;
      if (array_key_exists($field, $names)) {
        $name = $field . '_' . $names[$field];
        $names[$field]++;
      }
      else {
        $names[$field] = 1;
      }

      if (!empty($filter->options) && !empty($filter->options['exposed']) && $filter->options['expose']['multiple']) {
        $name = $name . '[]';
      }
      if ($selected_filters && !isset($selected_filters[$filter_key])) {
        continue;
      }
      $op = '=';
      $op_label = '=';
      if (!$filter->no_operator) {
        $op = $filter->operator;
        if (isset($operators[$op])) {
          $op_label = $operators[$op];
        }
        else {
          $op_label = $op;
        }
      }

      // Make sure that we do not display exposed filters that were not used.
      // E.g., check if a filter has a value.
      if (!empty($filter->value)) {

        if ($filter->table == 'node' && in_array($filter->field, array('title'))) {
          $filters_summary[$filter_key] = array(
            'label' => check_plain($filter->options['expose']['label']),
            'value' => array($filter->value),
            'op' => $op,
            'opLabel' => $op_label,
            'field' => $name,
          );
          continue;
        }

        // Get definition of field name.
        $field_name = FALSE;
        if (isset($filter->definition['field_name'])) {
          $field_name = $filter->definition['field_name'];
          $field_info = field_info_field($field_name);
        }

        // Get the type of field, or else use the handler for the fields which don't have a fieldname.
        if ($field_name) {
          $fieldtype = $field_info['type'];
        }
        else {
          $fieldtype = $filter->definition['handler'];
        }

        // Get the best label possible.
        $label = isset($filter->definition['title short']) ?
          $filter->definition['title short'] :
          $filter->definition['title'];
        if (isset($filter->options) && isset($filter->options['expose'])) {
          if (!empty($filter->options['expose']['label'])) {
            $label = $filter->options['expose']['label'];
          }
        }

        $filter_summary = array(
          'label' => check_plain($label),
          'value' => $filter->value,
          'raw_value' => $filter->value,
          'op' => $op,
          'opLabel' => $op_label,
          'field' => $name,
        );

        if (is_array($filter_summary['value'])) {
          foreach ($filter_summary['value'] as $key => $value) {
            $filter_summary['value'][$key] = check_plain($value);
          }
        }
        else {
          $filter_summary['value'] = check_plain($filter_summary['value']);
        }

        $include_filter = TRUE;

        // Check which type of filter it is.
        switch ($fieldtype) {
          case 'text_with_summary';

          case 'text';
            if (empty($filter_summary['value'])) {
              $include_filter = TRUE;
              break;
            }
            else {
              $filter_summary['value'] = array($filter_summary['value']);
            }
            break;

          case 'list_text':
            if (!empty($field_info['settings']['allowed_values'])) {
              foreach ($filter_summary['value'] as $key => $value) {
                $filter_summary['value'][$key] = $field_info['settings']['allowed_values'][$value];
              }
            }
            break;

          case 'taxonomy_term_reference':
          case 'views_handler_filter_term_node_tid':
          case 'views_handler_filter_term_node_tid_depth':
            foreach ($filter_summary['value'] as $key => $value) {
              $term = taxonomy_term_load($value);
              if ($term) {
                $filter_summary['value'][$key] = $term->name;
              }
            }
            break;

          case 'list_boolean':
            foreach ($filter_summary['value'] as $key => $value) {
              $filter_summary['value'][$key] = $filter_summary['value'][$key] == '1'
              || $filter_summary['value'][$key] == 'Yes' ? t('Yes') : t('No');
            }
            break;

          case 'datetime':

          case 'datestamp':

          case 'number_integer':

          case 'number_float':

          case 'number_decimal':
            $operator = array(
              '=',
              '>',
              '>=',
              '<',
              '<=',
              '!=',
              'regular_expression',
            );
            if (in_array($op, $operator)) {

              if (empty($filter_summary['value']['value'])) {
                $include_filter = FALSE;
                break;
              }
              $filter_summary['value'] = array($filter_summary['value']['value']);
            }
            elseif ($filter->operator == 'between') {
              if (empty($filter->value['min'])) {
                if (empty($filter->value['max'])) {
                  $include_filter = FALSE;
                  break;
                }
                else {
                  $filter_summary['opLabel'] = $fieldtype == 'datetime' ? t('before') : t('less than');
                  $filter_summary['value'] = array($filter_summary['value']['max']);
                }
              }
              else {
                if (empty($filter->value['max'])) {
                  $filter_summary['opLabel'] = $fieldtype == 'datetime' ? t('after') : t('more than');
                  $filter_summary['value'] = array($filter_summary['value']['min']);
                }
                else {
                  $filter_summary['opLabel'] = 'between';
                  $filter_summary['value'] = array(
                    $filter_summary['value']['min'],
                    $filter_summary['value']['max'],
                  );
                }
              }
            }
            elseif ($filter->operator == 'not between') {
              if (empty($filter->value['min'])) {
                if (empty($filter->value['max'])) {
                  $include_filter = FALSE;
                  break;
                }
                else {
                  $filter_summary['opLabel'] = t('greater than');
                  $filter_summary['value'] = array($filter_summary['value']['max']);
                }
              }
              else {
                if (empty($filter->value['max'])) {
                  $filter_summary['opLabel'] = t('less than');
                  $filter_summary['value'] = array($filter_summary['value']['min']);
                }
                else {
                  $filter_summary['opLabel'] = 'not between';
                  $filter_summary['value'] = array(
                    $filter_summary['value']['min'],
                    $filter_summary['value']['max'],
                  );
                }
              }
            }
            break;

          case 'entityreference':
            $items = entity_load($field_info['settings']['target_type'], array_values($filter->value));
            $res = array();
            foreach ($items as $item) {
              $uri = entity_uri($field_info['settings']['target_type'], $item);
              $title = entity_label($field_info['settings']['target_type'], $item);
              if (!empty($uri) && isset($uri['path'])) {
                $res[] = '<a href="' . $uri['path'] . '">' . $title . '</a>';
              }
              else {
                $res[] = $title;
              }
            }
            $filter_summary['value'] = $res;
            break;

          case 'views_handler_filter_combine':
            $filter_summary['value'] = array($filter->value);
            break;

          case 'views_handler_filter_user_name':
            foreach ($filter_summary['value'] as $key => $value) {
              $user = user_load($value);
              if ($user) {
                $filter_summary['value'][$key] = $user->name;
              }
            }
            break;

        }

        // Remove operators.
        if (!$show_operators) {
          $filter_summary['opLabel'] = ': ';
        }

        // Add label and value for this filter to our list.
        if ($include_filter && !empty($filter_summary['label'])) {
          $filters_summary[$filter_key] = $filter_summary;
        }
      }
    }

    return $filters_summary;
  }

}
