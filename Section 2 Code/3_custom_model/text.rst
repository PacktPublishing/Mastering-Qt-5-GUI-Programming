Welcome to Mastering Cute 5 GUI Programming, by Packt publishing. I'm Ben Hoff and this is Section 2.3, of the Diving into the model view section, which covers custom models.

In this section we're going to cover:
Why create custom models
How to choose our model subclass based on the data structure
and then walk through an example where we implement our own custom list model.

Let's go ahead and get started.

So first off, why would we create our own custom model? Especially if we've been getting by so well with the built in `QStandardItemModel`? 

Well some times our data is complex, comes from different sources, is dynamic, or is so expensive to query that we need to create our own models to get around these limitations. You will occasionally also run into corners of the Cute framework where the convince classes are also not powerful enough to implement what you need, requiring you to strike off on your own as well.

So if you know you need a custom model, what class should you use to base your implementation on? Well, it depends on your data structure.

If your data is represented by a list consider, using `QAbstractListModel`. If it's a Table `QAbstractTableModel`, and a tree structure will require you to subclass `QAbstractItemModel` completely. I would also encourage you to try and simplify your models if possible. So while your data may be a tree structure, it may be possible to display as a table if you get creative. Tricks like this will lower the complexity of your code.

But for now, let's go ahead and implement the simplest example, a `QAbstractListModel`. The nice thing about a list model, is that since the data isn't hierarchical we don't have to worry about the `index` and `parent` functions.

So let's go ahead and look at our model. We need to implement the `rowCount`, `data`, `setData`, and `flags` method.

So let's get cracking on implementing. The row count method is going to be very simple. Only the root node should return the list's size, for all other valid parents, rowCount should return a 0, so that our model never looks like a tree model to any view. So for any valid index, we'll return 0. For any non-valid, I.E. the root node, we'll return the size of colors.

.. code-block:: c++
  return colors.size();

For the data, all we're concerned with is passing back the Qt::DecorationRole. SO we'll check and return the color based on that.

.. code-block:: c++

  if (role == Qt::DecorationRole)
  {
    return colors[index.row()];
  }

For setting the data, we want to make sure that we're actually changing the data, so we'll check that first.

.. code-block:: c++

  if(data(index, role) != value)
  {
    colors[index.row()] = value.value<QColor>();
  }

Past that we need to let the view's know to update the data, so we'll emit a signal as well as let the view's know what role was changed.

.. code-block:: c++

  emit dataChanged(index, index, QVector<int>() << role);

In more complex models, we would do some validation that the change was good. We're going to skip that over here, but if your validation proved that your change wasn't valid you would return a `False` to show that the data wasn't changed. For this purpose, we'll return a true.

For all other setData's, we'll return False.

.. code-block:: c++

  return false;

The last thing that we want to do is re-implement the flags method call. The default flags include an `ItemIsSelectable` which obscures the color whenever we select an item in the view. 

Note that we don't need to pass any flags back for the root item, so we'll address that first.

.. code-block:: c++

  if (!index.isValid())
    return Qt::NoItemFlags;

  return Qt::ItemIsEnabled;

The item flags can be tricky. If we don't return the ItemIsEnabled, our pictures will all get returned in grayscale, which is a goofy thing to track down if you don't know where to look.

One thing that we're slightly gamming here, is that we don't return a Qt::ItemIsEditable command, even though we allow editing. We just don't edit using the typical item delegate that the view provides. If you look at the MainWindow implementation, we create a slot for changing colors and run a QDialog from there, as Qt's default for editing, the item delegates do not play well with QDialog's.

So let's go ahead and run this code and take a look.

So you can see, if we select any of the items we are able to change the color as we please, and that get's updated in the view.

And with that, we've successful implemented a custom list model, touched on the model/data relationship as well as talked about why create custom models.

Join us next time, where we implement a tree view.
