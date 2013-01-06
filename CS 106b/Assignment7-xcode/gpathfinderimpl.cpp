/*
 * File: gpathfinderimpl.cpp
 * -------------------------
 * This function implements the template functions addButton
 * and addClickListener.  C++ requires that this code be
 * available at the time the interface is read, but clients
 * are not expected to look at this code.
 */

#ifdef _gpathfinder_h

/*
 * Implementation notes: callback classes
 * --------------------------------------
 * The task of storing a callback function that is triggered
 * at the time of a mouse or button click is more difficult that
 * it might at first appear.  The complexity arises from the fact
 * that the ClientDataType parameter to the callback function is
 * supplied at the time the button is declared but used in the
 * implementation of PathfinderEventLoop, which no longer has
 * access to the ClientDataType information.  To solve this
 * problem, the callback functions and the address of the
 * client data object are stored in a template subclass of
 * a standard base class containing a virtual apply method.
 * When PathfinderEventLoop wants to trigger the callback
 * action, it calls the apply method of the base class, which
 * then invokes the specific code for the relevant subclass
 * that knows the identity of ClientDataType.  The base classes
 * are also used on their own to implement the callbacks when
 * no ClientDataType value is supplied.
 */

class ButtonCallbackBase {
public:
   ButtonCallbackBase();
   ButtonCallbackBase(void (*actionFn)());
   virtual ~ButtonCallbackBase();
   virtual void apply();

private:
   void (*actionFn)();
};

template <typename ClientDataType>
class ButtonCallback : public ButtonCallbackBase {
public:
   ButtonCallback(void (*actionFn)(ClientDataType & data), ClientDataType *pdata);
   virtual ~ButtonCallback();
   virtual void apply();

private:
   void (*actionFn)(ClientDataType & data);
   ClientDataType *pdata;
};

template <typename ClientDataType>
ButtonCallback<ClientDataType>::ButtonCallback(void (*actionFn)(ClientDataType & data),
                                               ClientDataType *pdata) {
   this->actionFn = actionFn;
   this->pdata = pdata;
}

template <typename ClientDataType>
ButtonCallback<ClientDataType>::~ButtonCallback() {
   /* Empty */
}

template <typename ClientDataType>
void ButtonCallback<ClientDataType>::apply() {
   actionFn(*pdata);
}

class ClickCallbackBase {
public:
   ClickCallbackBase();
   ClickCallbackBase(void (*clickFn)(GPoint pt));
   virtual ~ClickCallbackBase();
   virtual void apply(GPoint pt);

private:
   void (*clickFn)(GPoint pt);
};

template <typename ClientDataType>
class ClickCallback : public ClickCallbackBase {
public:
   ClickCallback(void (*clickFn)(GPoint pt, ClientDataType & data),
                 ClientDataType *pdata);
   virtual ~ClickCallback();
   virtual void apply(GPoint pt);

private:
   void (*clickFn)(GPoint pt, ClientDataType & data);
   ClientDataType *pdata;
};

template <typename ClientDataType>
ClickCallback<ClientDataType>::ClickCallback(
              void (*clickFn)(GPoint pt, ClientDataType & data),
              ClientDataType *pdata) {
   this->clickFn = clickFn;
   this->pdata = pdata;
}

template <typename ClientDataType>
ClickCallback<ClientDataType>::~ClickCallback() {
   /* Empty */
}

template <typename ClientDataType>
void ClickCallback<ClientDataType>::apply(GPoint pt) {
   clickFn(pt, *pdata);
}

/* Prototypes for functions in gpathfinder.cpp */

void addButton(string name, ButtonCallbackBase *callback);
void defineClickListener(ClickCallbackBase *callback);

/*
 * Implementation notes: addButton, defineClickListener
 * ----------------------------------------------------
 * These template functions create the appropriate callback
 * structure and then call a non-template function in
 * gpathfinder.cpp that works with the base class
 * of that object and therefore no longer requires the
 * overhead of C++'s template mechanism.
 */

template <typename ClientDataType>
void addButton(string name,
               void (*actionFn)(ClientDataType & data),
               ClientDataType & data) {
   addButton(name, new ButtonCallback<ClientDataType>(actionFn, &data));
}

template <typename ClientDataType>
void defineClickListener(void (*clickFn)(GPoint pt, ClientDataType & data),
                         ClientDataType & data) {
   defineClickListener(new ClickCallback<ClientDataType>(clickFn, &data));
}

#endif

